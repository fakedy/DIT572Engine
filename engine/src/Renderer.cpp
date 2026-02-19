#include <Engine/Renderer.h>
#include <Engine/WindowManager.h>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <Engine/Texture.h>

namespace Engine {
	Renderer::Renderer()
	{

		m_gpuDevice = SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_SPIRV | SDL_GPU_SHADERFORMAT_DXIL | SDL_GPU_SHADERFORMAT_MSL, true, "vulkan");

	}

	Renderer::~Renderer()
	{
		SDL_DestroyGPUDevice(m_gpuDevice);
	}

	int Renderer::init() {


		SDL_ClaimWindowForGPUDevice(m_gpuDevice, Engine::WindowManager::Get().getWindow());
		

		// Create depth texture
		SDL_GPUTextureCreateInfo depthTextureInfo = {};
		depthTextureInfo.type = SDL_GPU_TEXTURETYPE_2D;
		depthTextureInfo.format = SDL_GPU_TEXTUREFORMAT_D16_UNORM;
		depthTextureInfo.width = m_windowWidth;
		depthTextureInfo.height = m_windowHeight;
		depthTextureInfo.layer_count_or_depth = 1;
		depthTextureInfo.num_levels = 1;
		depthTextureInfo.usage = SDL_GPU_TEXTUREUSAGE_DEPTH_STENCIL_TARGET;
		m_depthTexture = SDL_CreateGPUTexture(m_gpuDevice, &depthTextureInfo);


		// a pipeline must be created for each shader program
		SDL_GPUShader* vertexShader = createShader("Assets/shaders/vDefault.spv", SDL_GPU_SHADERFORMAT_SPIRV, SDL_GPU_SHADERSTAGE_VERTEX, 0, 1, 0, 0);
		SDL_GPUShader* fragmentShader = createShader("Assets/shaders/fDefault.spv", SDL_GPU_SHADERFORMAT_SPIRV, SDL_GPU_SHADERSTAGE_FRAGMENT, 1, 0, 0, 0);

		SDL_GPUGraphicsPipelineCreateInfo spritePipelineInfo = {0};
		spritePipelineInfo.vertex_shader = vertexShader;
		spritePipelineInfo.fragment_shader = fragmentShader;

		// enable depth testing
		spritePipelineInfo.depth_stencil_state.enable_depth_test = true;
		spritePipelineInfo.depth_stencil_state.enable_depth_write = true;
		spritePipelineInfo.depth_stencil_state.compare_op = SDL_GPU_COMPAREOP_LESS;

		spritePipelineInfo.target_info.has_depth_stencil_target = true;
		spritePipelineInfo.target_info.depth_stencil_format = SDL_GPU_TEXTUREFORMAT_D16_UNORM;


		SDL_GPUColorTargetDescription colorTarget = {};
		colorTarget.format = SDL_GetGPUSwapchainTextureFormat(m_gpuDevice, Engine::WindowManager::Get().getWindow());

		// this is like glBlendFunc except you have to set it all yourself...
		colorTarget.blend_state.enable_blend = true;
		colorTarget.blend_state.src_color_blendfactor = SDL_GPU_BLENDFACTOR_SRC_ALPHA;
		colorTarget.blend_state.dst_color_blendfactor = SDL_GPU_BLENDFACTOR_ONE_MINUS_SRC_ALPHA;
		colorTarget.blend_state.color_blend_op = SDL_GPU_BLENDOP_ADD;

		colorTarget.blend_state.src_alpha_blendfactor = SDL_GPU_BLENDFACTOR_ONE;
		colorTarget.blend_state.dst_alpha_blendfactor = SDL_GPU_BLENDFACTOR_ZERO;
		colorTarget.blend_state.alpha_blend_op = SDL_GPU_BLENDOP_ADD;

		colorTarget.blend_state.color_write_mask = 0xF; // RGBA because 0b1111


		spritePipelineInfo.target_info.color_target_descriptions = &colorTarget;
		spritePipelineInfo.target_info.num_color_targets = 1;
		spritePipelineInfo.primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST;

		// basically attribinfo for the pipeline
		// this is all like setting up the VAO
		SDL_GPUVertexAttribute vertAttribs[2];
		vertAttribs[0] = { 0, 0, SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3, 0 }; // positions
		vertAttribs[1] = { 1, 0, SDL_GPU_VERTEXELEMENTFORMAT_FLOAT2, sizeof(float) * 3}; // uv

		SDL_GPUVertexBufferDescription vertBufferDesc = {};
		vertBufferDesc.slot = 0;
		vertBufferDesc.pitch = sizeof(float) * 5; // stride, 3 positions, 2 uv coordinates
		vertBufferDesc.input_rate = SDL_GPU_VERTEXINPUTRATE_VERTEX;
		vertBufferDesc.instance_step_rate = 0; // unused

		spritePipelineInfo.vertex_input_state.vertex_attributes = vertAttribs;
		spritePipelineInfo.vertex_input_state.num_vertex_attributes = 2;

		spritePipelineInfo.vertex_input_state.vertex_buffer_descriptions = &vertBufferDesc;
		spritePipelineInfo.vertex_input_state.num_vertex_buffers = 1;

		m_spritePipeline = SDL_CreateGPUGraphicsPipeline(m_gpuDevice, &spritePipelineInfo);

		// shaders are not needed anymore!!!
		SDL_ReleaseGPUShader(m_gpuDevice, vertexShader);
		SDL_ReleaseGPUShader(m_gpuDevice, fragmentShader);

		// setup buffer

		SDL_GPUBufferCreateInfo bufferInfo = {};
		bufferInfo.props = 0;
		bufferInfo.size = sizeof(m_vertices);
		bufferInfo.usage = SDL_GPU_BUFFERUSAGE_VERTEX;

		m_quadVertexBuffer = SDL_CreateGPUBuffer(m_gpuDevice, &bufferInfo);

		bufferInfo.props = 0;
		bufferInfo.size = sizeof(m_indices);
		bufferInfo.usage = SDL_GPU_BUFFERUSAGE_INDEX;

		m_quadIndicesBuffer = SDL_CreateGPUBuffer(m_gpuDevice, &bufferInfo);

		// upload buffer
		SDL_GPUTransferBufferCreateInfo transferBufferInfo = {};
		transferBufferInfo.props = 0;
		transferBufferInfo.size = sizeof(m_vertices) + sizeof(m_indices);

		SDL_GPUTransferBuffer* bufferTransferBuffer = SDL_CreateGPUTransferBuffer(m_gpuDevice, &transferBufferInfo);

		void* mappedData = SDL_MapGPUTransferBuffer(m_gpuDevice, bufferTransferBuffer, false);
		SDL_memcpy(mappedData, m_vertices, sizeof(m_vertices));
		SDL_memcpy((uint8_t*)mappedData + sizeof(m_vertices), m_indices, sizeof(m_indices)); // put indices at offset of (uint8_t*)mappedData + sizeof(vertices)
		SDL_UnmapGPUTransferBuffer(m_gpuDevice, bufferTransferBuffer);


		// command buffer for uploading

		SDL_GPUCommandBuffer* uploadCmdBuffer = SDL_AcquireGPUCommandBuffer(m_gpuDevice);
		SDL_GPUCopyPass* copyPass = SDL_BeginGPUCopyPass(uploadCmdBuffer);


		// Uploading quad vertices to GPU
		{
			SDL_GPUTransferBufferLocation transferbufferloc = {};
			transferbufferloc.offset = 0;
			transferbufferloc.transfer_buffer = bufferTransferBuffer;

			SDL_GPUBufferRegion bufferRegion = {};
			bufferRegion.buffer = m_quadVertexBuffer;
			bufferRegion.offset = 0;
			bufferRegion.size = sizeof(m_vertices);

			SDL_UploadToGPUBuffer(copyPass, &transferbufferloc, &bufferRegion, false);
		}

		// Uploading quad Indices to GPU
		{
			SDL_GPUTransferBufferLocation transferbufferloc = {};
			transferbufferloc.offset = sizeof(m_vertices);
			transferbufferloc.transfer_buffer = bufferTransferBuffer;

			SDL_GPUBufferRegion bufferRegion = {};
			bufferRegion.buffer = m_quadIndicesBuffer;
			bufferRegion.offset = 0;
			bufferRegion.size = sizeof(m_indices);

			SDL_UploadToGPUBuffer(copyPass, &transferbufferloc, &bufferRegion, false);
		}


		SDL_EndGPUCopyPass(copyPass);
		SDL_SubmitGPUCommandBuffer(uploadCmdBuffer);
		SDL_ReleaseGPUTransferBuffer(m_gpuDevice, bufferTransferBuffer);

		// samplers

		SDL_GPUSamplerCreateInfo SamplerNearest = {};
		SamplerNearest.props = 0;
		SamplerNearest.min_filter = SDL_GPU_FILTER_NEAREST;
		SamplerNearest.mag_filter = SDL_GPU_FILTER_NEAREST;
		SamplerNearest.mipmap_mode = SDL_GPU_SAMPLERMIPMAPMODE_NEAREST;
		SamplerNearest.address_mode_u = SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE;
		SamplerNearest.address_mode_v = SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE;
		SamplerNearest.address_mode_w = SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE;

		m_samplerNearest = SDL_CreateGPUSampler(m_gpuDevice, &SamplerNearest);

		SDL_GPUSamplerCreateInfo SamplerLinear = {};
		SamplerLinear.props = 0;
		SamplerLinear.min_filter = SDL_GPU_FILTER_LINEAR;
		SamplerLinear.mag_filter = SDL_GPU_FILTER_LINEAR;
		SamplerLinear.mipmap_mode = SDL_GPU_SAMPLERMIPMAPMODE_LINEAR;
		SamplerLinear.address_mode_u = SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE;
		SamplerLinear.address_mode_v = SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE;
		SamplerLinear.address_mode_w = SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE;

		m_samplerLinear = SDL_CreateGPUSampler(m_gpuDevice, &SamplerLinear);

		SDL_GPUSamplerCreateInfo SamplerRepeat = {};
		SamplerRepeat.props = 0;
		SamplerRepeat.min_filter = SDL_GPU_FILTER_NEAREST;
		SamplerRepeat.mag_filter = SDL_GPU_FILTER_NEAREST;
		SamplerRepeat.mipmap_mode = SDL_GPU_SAMPLERMIPMAPMODE_NEAREST;
		SamplerRepeat.address_mode_u = SDL_GPU_SAMPLERADDRESSMODE_REPEAT;
		SamplerRepeat.address_mode_v = SDL_GPU_SAMPLERADDRESSMODE_REPEAT;
		SamplerRepeat.address_mode_w = SDL_GPU_SAMPLERADDRESSMODE_REPEAT;

		m_samplerRepeat = SDL_CreateGPUSampler(m_gpuDevice, &SamplerRepeat);


		return 0;
	}


	void Renderer::draw() {

		// this is hardcoded to draw quads right now lol

		// create command buffer (for render commands)
		SDL_GPUCommandBuffer* cmd = SDL_AcquireGPUCommandBuffer(m_gpuDevice);
		// the texture displayed on screen
		SDL_GPUTexture* swapchainTexture;

		// if we cant get the swapchainTexture (the window is closed)
		if (!SDL_AcquireGPUSwapchainTexture(cmd, Engine::WindowManager::Get().getWindow(), &swapchainTexture, nullptr, nullptr)) {
			SDL_SubmitGPUCommandBuffer(cmd);
			return;
		}
		
		// render pass

		// color target
		SDL_GPUColorTargetInfo colorTargetInfo = { 0 };
		colorTargetInfo.texture = swapchainTexture;
		colorTargetInfo.clear_color = { 0.3f, 0.3f, 0.8f, 1.0f };
		colorTargetInfo.load_op = SDL_GPU_LOADOP_CLEAR; // clear on load 
		colorTargetInfo.store_op = SDL_GPU_STOREOP_STORE; // write to memory

		// depth target

		SDL_GPUDepthStencilTargetInfo depthTargetInfo = {};
		depthTargetInfo.texture = m_depthTexture;
		depthTargetInfo.clear_depth = 1.0f;
		depthTargetInfo.load_op = SDL_GPU_LOADOP_CLEAR;
		depthTargetInfo.store_op = SDL_GPU_STOREOP_DONT_CARE;
		depthTargetInfo.stencil_load_op = SDL_GPU_LOADOP_DONT_CARE;
		depthTargetInfo.stencil_store_op = SDL_GPU_STOREOP_DONT_CARE;
		depthTargetInfo.cycle = true;

		// only works for 2d right now
		SDL_GPURenderPass* renderPass = SDL_BeginGPURenderPass(cmd, &colorTargetInfo, 1, &depthTargetInfo);

		SDL_BindGPUGraphicsPipeline(renderPass, m_spritePipeline);


		SDL_GPUBufferBinding vertexBufferBinding = {};
		vertexBufferBinding.buffer = m_quadVertexBuffer;
		vertexBufferBinding.offset = 0;

		SDL_BindGPUVertexBuffers(renderPass, 0, &vertexBufferBinding, 1);

		SDL_GPUBufferBinding indexBufferBinding = {};
		indexBufferBinding.buffer = m_quadIndicesBuffer;
		indexBufferBinding.offset = 0;
		SDL_BindGPUIndexBuffer(renderPass, &indexBufferBinding, SDL_GPU_INDEXELEMENTSIZE_16BIT);



		// matches the shader uniform
		struct DataBlock {
			glm::mat4 model;
			glm::mat4 proj;
			glm::mat4 view;
			glm::vec2 uvScale;
		};

		DataBlock ubo;

		for (auto& camera : m_cameras) {

			// skip inactive cameras
			if (!camera->isActive)
				continue;

			ubo.proj = camera->getProjection();
			ubo.view = camera->getView();

			for (auto& pair : m_renderObjects) {

				SDL_GPUTextureSamplerBinding textureBinding = {};
				Material& mat = pair.second->getMaterial();
				textureBinding.texture = mat.texture->textureHandle; // From AssetManager
				textureBinding.sampler = m_samplerNearest;
				ubo.uvScale = glm::vec2(1, 1);
				// check sampler
				if (mat.samplerMode == Material::SAMPLER_MODE_REPEAT) {
					textureBinding.sampler = m_samplerRepeat;
					ubo.uvScale = pair.second->uvScale;
				}
				else if (mat.samplerMode == Material::SAMPLER_MODE_LINEAR) {
					textureBinding.sampler = m_samplerLinear;
				}
				else {
					textureBinding.sampler = m_samplerNearest;
				}

				SDL_BindGPUFragmentSamplers(renderPass, 0, &textureBinding, 1);

				glm::mat4 model = pair.second->getModel();
				Material& material = pair.second->getMaterial();
				float sizeX = (float)material.texture->width / pixels_per_unit;
				float sizeY = (float)material.texture->height / pixels_per_unit;
				glm::mat4 tempModel = glm::scale(model, glm::vec3(sizeX, sizeY, 1.0f));
				ubo.model = tempModel;

				SDL_PushGPUVertexUniformData(cmd, 0, &ubo, sizeof(ubo));
				SDL_DrawGPUIndexedPrimitives(renderPass, 6, 1, 0, 0, 0);
			}
		}

		// cleanup

		SDL_EndGPURenderPass(renderPass);
		SDL_SubmitGPUCommandBuffer(cmd);

	}

	SDL_GPUDevice& Renderer::getDevice()
	{
		return *m_gpuDevice;
	}



	int Renderer::addRenderObject(RenderComponent* sprite)
	{
		int id = m_nextRenderObject++;
		m_renderObjects[id] = sprite;
		return id;
	}

	void Renderer::removeSprite(int id)
	{
		m_renderObjects.erase(id);
	}

	void Renderer::handleResizeWindow(unsigned int width, unsigned int height) 
	{

		m_windowHeight = height;
		m_windowWidth = width;

		float aspectRatio = (float)m_windowWidth / (float)m_windowHeight;

		
		float orthoHeight = m_unitHeight / 2.0f;
		float orthoWidth = orthoHeight * aspectRatio;


		// since the projection depends on screen resolution this is required
		for (auto& camera : m_cameras) {
			if (camera->isActive) {
				camera->orthoWidth = orthoWidth;
				camera->orthoHeight = orthoHeight;
				camera->updateProjection();
			}
		}

		// On resize we have to delete the old depth texture
		if (m_depthTexture != nullptr) {
			SDL_ReleaseGPUTexture(m_gpuDevice, m_depthTexture);
			m_depthTexture = nullptr;
		}

		// recreate the depth buffer texture
		SDL_GPUTextureCreateInfo depthTextureInfo = {};
		depthTextureInfo.type = SDL_GPU_TEXTURETYPE_2D;
		depthTextureInfo.format = SDL_GPU_TEXTUREFORMAT_D16_UNORM;
		depthTextureInfo.width = m_windowWidth;
		depthTextureInfo.height = m_windowHeight;
		depthTextureInfo.layer_count_or_depth = 1;
		depthTextureInfo.num_levels = 1;
		depthTextureInfo.usage = SDL_GPU_TEXTUREUSAGE_DEPTH_STENCIL_TARGET;
		m_depthTexture = SDL_CreateGPUTexture(m_gpuDevice, &depthTextureInfo);


		SDL_Log("Window resized to % dx % d\n", width, height);
		SDL_Log("Window Units resized to % f % f\n", orthoWidth, orthoHeight);


	}

	SDL_GPUShader* Renderer::createShader(const char* shaderPath, SDL_GPUShaderFormat format, SDL_GPUShaderStage stage
		, Uint32 numSamplers, Uint32 numUniformBuffers, Uint32 numStorageBuffers, Uint32 numStorageTextures)
	{

		size_t dataSize;
		void* data = SDL_LoadFile(shaderPath, &dataSize);

		SDL_GPUShaderCreateInfo vertexCreateInfo = { 0 };
		vertexCreateInfo.code = static_cast<Uint8*>(data);
		vertexCreateInfo.code_size = dataSize;
		vertexCreateInfo.entrypoint = "main";
		vertexCreateInfo.format = format;
		vertexCreateInfo.stage = stage;
		vertexCreateInfo.num_uniform_buffers = numUniformBuffers;
		vertexCreateInfo.num_samplers = numSamplers;
		vertexCreateInfo.num_storage_buffers = numStorageBuffers;
		


		SDL_GPUShader*  shader = SDL_CreateGPUShader(m_gpuDevice, &vertexCreateInfo);

		SDL_free(data);

		return shader;
	}

	int Renderer::addCamera(Camera* camera)
	{
		m_cameras.push_back(camera);

		float aspectRatio = (float)m_windowWidth / (float)m_windowHeight;
		float orthoHeight = m_unitHeight / 2.0f;
		float orthoWidth = orthoHeight * aspectRatio;

		camera->orthoWidth = orthoWidth;
		camera->orthoHeight = orthoHeight;
		camera->updateProjection();

		return m_cameras.size() - 1;
	}


	

}
