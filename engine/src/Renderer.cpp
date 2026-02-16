#include <Engine/Renderer.h>
#include <Engine/WindowManager.h>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <Engine/Texture.h>

namespace Engine {
	Renderer::Renderer()
	{

		_gpuDevice = SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_SPIRV | SDL_GPU_SHADERFORMAT_DXIL | SDL_GPU_SHADERFORMAT_MSL, true, "vulkan");

	}

	Renderer::~Renderer()
	{
		SDL_DestroyGPUDevice(_gpuDevice);
	}

	int Renderer::init() {


		SDL_ClaimWindowForGPUDevice(_gpuDevice, Engine::WindowManager::Get().getWindow());
		
		// a pipeline must be created for each shader program

		SDL_GPUShader* vertexShader = createShader("assets/shaders/vDefault.spv", SDL_GPU_SHADERFORMAT_SPIRV, SDL_GPU_SHADERSTAGE_VERTEX, 0, 1, 0, 0);
		SDL_GPUShader* fragmentShader = createShader("assets/shaders/fDefault.spv", SDL_GPU_SHADERFORMAT_SPIRV, SDL_GPU_SHADERSTAGE_FRAGMENT, 1, 0, 0, 0);

		SDL_GPUGraphicsPipelineCreateInfo spritePipelineInfo = {0};
		spritePipelineInfo.vertex_shader = vertexShader;
		spritePipelineInfo.fragment_shader = fragmentShader;


		SDL_GPUColorTargetDescription colorTarget = {};
		colorTarget.format = SDL_GetGPUSwapchainTextureFormat(_gpuDevice, Engine::WindowManager::Get().getWindow());

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

		_spritePipeline = SDL_CreateGPUGraphicsPipeline(_gpuDevice, &spritePipelineInfo);

		// shaders are not needed anymore!!!
		SDL_ReleaseGPUShader(_gpuDevice, vertexShader);
		SDL_ReleaseGPUShader(_gpuDevice, fragmentShader);

		// setup buffer

		SDL_GPUBufferCreateInfo bufferInfo = {};
		bufferInfo.props = 0;
		bufferInfo.size = sizeof(vertices);
		bufferInfo.usage = SDL_GPU_BUFFERUSAGE_VERTEX;

		quadVertexBuffer = SDL_CreateGPUBuffer(_gpuDevice, &bufferInfo);

		bufferInfo.props = 0;
		bufferInfo.size = sizeof(indices);
		bufferInfo.usage = SDL_GPU_BUFFERUSAGE_INDEX;

		quadIndicesBuffer = SDL_CreateGPUBuffer(_gpuDevice, &bufferInfo);

		// upload buffer
		SDL_GPUTransferBufferCreateInfo transferBufferInfo = {};
		transferBufferInfo.props = 0;
		transferBufferInfo.size = sizeof(vertices) + sizeof(indices);

		SDL_GPUTransferBuffer* bufferTransferBuffer = SDL_CreateGPUTransferBuffer(_gpuDevice, &transferBufferInfo);

		void* mappedData = SDL_MapGPUTransferBuffer(_gpuDevice, bufferTransferBuffer, false);
		SDL_memcpy(mappedData, vertices, sizeof(vertices));
		SDL_memcpy((uint8_t*)mappedData + sizeof(vertices), indices, sizeof(indices)); // put indices at offset of (uint8_t*)mappedData + sizeof(vertices)
		SDL_UnmapGPUTransferBuffer(_gpuDevice, bufferTransferBuffer);


		// command buffer for uploading

		SDL_GPUCommandBuffer* uploadCmdBuffer = SDL_AcquireGPUCommandBuffer(_gpuDevice);
		SDL_GPUCopyPass* copyPass = SDL_BeginGPUCopyPass(uploadCmdBuffer);


		{
			SDL_GPUTransferBufferLocation transferbufferloc = {};
			transferbufferloc.offset = 0;
			transferbufferloc.transfer_buffer = bufferTransferBuffer;

			SDL_GPUBufferRegion bufferRegion = {};
			bufferRegion.buffer = quadVertexBuffer;
			bufferRegion.offset = 0;
			bufferRegion.size = sizeof(vertices);

			SDL_UploadToGPUBuffer(copyPass, &transferbufferloc, &bufferRegion, false);
		}

		{
			SDL_GPUTransferBufferLocation transferbufferloc = {};
			transferbufferloc.offset = sizeof(vertices);
			transferbufferloc.transfer_buffer = bufferTransferBuffer;

			SDL_GPUBufferRegion bufferRegion = {};
			bufferRegion.buffer = quadIndicesBuffer;
			bufferRegion.offset = 0;
			bufferRegion.size = sizeof(indices);

			SDL_UploadToGPUBuffer(copyPass, &transferbufferloc, &bufferRegion, false);
		}


		SDL_EndGPUCopyPass(copyPass);
		SDL_SubmitGPUCommandBuffer(uploadCmdBuffer);
		SDL_ReleaseGPUTransferBuffer(_gpuDevice, bufferTransferBuffer);

		// this is a basic sprite smapler
		// we probably want multiple samplers and then select which one we want when rendering?
		SDL_GPUSamplerCreateInfo spriteSamplerInfo = {};
		spriteSamplerInfo.props = 0;
		spriteSamplerInfo.min_filter = SDL_GPU_FILTER_NEAREST;
		spriteSamplerInfo.mag_filter = SDL_GPU_FILTER_NEAREST;
		spriteSamplerInfo.mipmap_mode = SDL_GPU_SAMPLERMIPMAPMODE_NEAREST;
		spriteSamplerInfo.address_mode_u = SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE;
		spriteSamplerInfo.address_mode_v = SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE;
		spriteSamplerInfo.address_mode_w = SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE;

		_spriteSampler = SDL_CreateGPUSampler(_gpuDevice, &spriteSamplerInfo);

		// this should be related to what camera is used, several cameras should be able to be used at once

		float aspectRatio = (float)windowWidth / (float)windowHeight;


		float orthoHeight = unitHeight / 2.0f;
		float orthoWidth = orthoHeight * aspectRatio;

		proj = glm::ortho(-orthoWidth, orthoWidth, -orthoHeight, orthoHeight, -1.0f, 1.0f);


		return 0;
	}


	void Renderer::draw() {

		// this is hardcoded to draw quads right now lol

		// create command buffer (for render commands)
		SDL_GPUCommandBuffer* cmd = SDL_AcquireGPUCommandBuffer(_gpuDevice);
		// the texture displayed on screen
		SDL_GPUTexture* swapchainTexture;

		// if we cant get the swapchainTexture (the window is closed)
		if (!SDL_AcquireGPUSwapchainTexture(cmd, Engine::WindowManager::Get().getWindow(), &swapchainTexture, nullptr, nullptr)) {
			SDL_SubmitGPUCommandBuffer(cmd);
			return;
		}
		
		// render pass

		SDL_GPUColorTargetInfo colorTargetInfo = { 0 };
		colorTargetInfo.texture = swapchainTexture;
		colorTargetInfo.clear_color = { 0.3f, 0.3f, 0.8f, 1.0f };
		colorTargetInfo.load_op = SDL_GPU_LOADOP_CLEAR; // clear on load 
		colorTargetInfo.store_op = SDL_GPU_STOREOP_STORE; // write to memory

		// only works for 2d right now
		SDL_GPURenderPass* renderPass = SDL_BeginGPURenderPass(cmd, &colorTargetInfo, 1, nullptr);

		SDL_BindGPUGraphicsPipeline(renderPass, _spritePipeline);


		SDL_GPUBufferBinding vertexBufferBinding = {};
		vertexBufferBinding.buffer = quadVertexBuffer;
		vertexBufferBinding.offset = 0;

		SDL_BindGPUVertexBuffers(renderPass, 0, &vertexBufferBinding, 1);

		SDL_GPUBufferBinding indexBufferBinding = {};
		indexBufferBinding.buffer = quadIndicesBuffer;
		indexBufferBinding.offset = 0;
		SDL_BindGPUIndexBuffer(renderPass, &indexBufferBinding, SDL_GPU_INDEXELEMENTSIZE_16BIT);



		// matches the shader uniform
		struct DataBlock {
			glm::mat4 model;
			glm::mat4 proj;
		};

		DataBlock ubo;

		for (auto& camera : cameras) {

			if (!camera->isActive)
				continue;

			ubo.proj = camera->getProjection();

			for (auto& pair : RenderObjects) {

				SDL_GPUTextureSamplerBinding textureBinding = {};
				textureBinding.texture = pair.second->getMaterial().texture->textureHandle; // From AssetManager
				textureBinding.sampler = _spriteSampler;
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


	// unused 
	void Renderer::drawSprite(glm::mat4 model, Material& material)
	{
	}

	SDL_GPUDevice& Renderer::getDevice()
	{
		return *_gpuDevice;
	}



	int Renderer::addRenderObject(RenderComponent* sprite)
	{
		int id = nextRenderObject++;
		RenderObjects[id] = sprite;
		return id;
	}

	void Renderer::removeSprite(int id)
	{
		RenderObjects.erase(id);
	}

	void Renderer::handleResizeWindow(unsigned int width, unsigned int height) 
	{

		windowHeight = height;
		windowWidth = width;

		float aspectRatio = (float)windowWidth / (float)windowHeight;
		float orthoHeight = unitHeight / 2.0f;
		float orthoWidth = orthoHeight * aspectRatio;

		for (auto& camera : cameras) {
			if (camera->isActive) {
				camera->orthoWidth = orthoWidth;
				camera->orthoHeight = orthoHeight;
				camera->updateProjection();
			}
		}

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
		


		SDL_GPUShader*  shader = SDL_CreateGPUShader(_gpuDevice, &vertexCreateInfo);

		SDL_free(data);

		return shader;
	}

	int Renderer::addCamera(Camera* camera)
	{
		cameras.push_back(camera);

		float aspectRatio = (float)windowWidth / (float)windowHeight;
		float orthoHeight = unitHeight / 2.0f;
		float orthoWidth = orthoHeight * aspectRatio;

		camera->orthoWidth = orthoWidth;
		camera->orthoHeight = orthoHeight;
		camera->updateProjection();

		return cameras.size() - 1;
	}


	

}