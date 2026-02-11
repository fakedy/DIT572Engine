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
		// for now 2 types should be enough for what we want to do
		SDL_GPUGraphicsPipelineCreateInfo spritePipelineInfo = {0};
		spritePipelineInfo.vertex_shader = createShader("assets/shaders/vDefault.spv", SDL_GPU_SHADERFORMAT_SPIRV, SDL_GPU_SHADERSTAGE_VERTEX, 0, 1, 0, 0);
		spritePipelineInfo.fragment_shader = createShader("assets/shaders/fDefault.spv", SDL_GPU_SHADERFORMAT_SPIRV, SDL_GPU_SHADERSTAGE_FRAGMENT, 1, 0, 0, 0);


		SDL_GPUColorTargetDescription colorTarget;
		colorTarget.format = SDL_GetGPUSwapchainTextureFormat(_gpuDevice, Engine::WindowManager::Get().getWindow());

		// this is like glBlendFunc except you have to set it all yourself...
		colorTarget.blend_state.enable_blend = true;
		colorTarget.blend_state.src_color_blendfactor = SDL_GPU_BLENDFACTOR_SRC_ALPHA;
		colorTarget.blend_state.dst_color_blendfactor = SDL_GPU_BLENDFACTOR_ONE_MINUS_SRC_ALPHA;
		colorTarget.blend_state.color_blend_op = SDL_GPU_BLENDOP_ADD;

		colorTarget.blend_state.src_alpha_blendfactor = SDL_GPU_BLENDFACTOR_ONE;
		colorTarget.blend_state.dst_alpha_blendfactor = SDL_GPU_BLENDFACTOR_ZERO;
		colorTarget.blend_state.alpha_blend_op = SDL_GPU_BLENDOP_ADD;

		colorTarget.blend_state.color_write_mask = 0xF; 


		spritePipelineInfo.target_info.color_target_descriptions = &colorTarget;
		spritePipelineInfo.target_info.num_color_targets = 1;
		spritePipelineInfo.primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST;

		// this is all like setting up the VAO
		SDL_GPUVertexAttribute vertAttribs[2];
		vertAttribs[0] = { 0, 0, SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3, 0 }; // positions
		vertAttribs[1] = { 1, 0, SDL_GPU_VERTEXELEMENTFORMAT_FLOAT2, sizeof(float) * 3}; // uv

		SDL_GPUVertexBufferDescription vertBufferDesc = {};
		vertBufferDesc.slot = 0;
		vertBufferDesc.pitch = sizeof(vertices);
		vertBufferDesc.input_rate = SDL_GPU_VERTEXINPUTRATE_VERTEX;
		vertBufferDesc.instance_step_rate = 0; // unused

		spritePipelineInfo.vertex_input_state.vertex_attributes = vertAttribs;
		spritePipelineInfo.vertex_input_state.num_vertex_attributes = 2;

		spritePipelineInfo.vertex_input_state.vertex_buffer_descriptions = &vertBufferDesc;
		spritePipelineInfo.vertex_input_state.num_vertex_buffers = 1;

		_spritePipeline = SDL_CreateGPUGraphicsPipeline(_gpuDevice, &spritePipelineInfo);


		// setup buffer

		SDL_GPUBufferCreateInfo bufferInfo;
		bufferInfo.props = 0;
		bufferInfo.size = sizeof(vertices);
		bufferInfo.usage = SDL_GPU_BUFFERUSAGE_VERTEX;

		quadVertexBuffer = SDL_CreateGPUBuffer(_gpuDevice, &bufferInfo);

		bufferInfo.props = 0;
		bufferInfo.size = sizeof(indices);
		bufferInfo.usage = SDL_GPU_BUFFERUSAGE_INDEX;

		quadIndicesBuffer = SDL_CreateGPUBuffer(_gpuDevice, &bufferInfo);

		// upload buffer
		SDL_GPUTransferBufferCreateInfo transferBufferInfo;
		transferBufferInfo.props = 0;
		transferBufferInfo.size = sizeof(vertices) + sizeof(indices);

		SDL_GPUTransferBuffer* bufferTransferBuffer = SDL_CreateGPUTransferBuffer(_gpuDevice, &transferBufferInfo);

		void* mappedData = SDL_MapGPUTransferBuffer(_gpuDevice, bufferTransferBuffer, false);
		memcpy(mappedData, vertices, sizeof(vertices));
		memcpy((uint8_t*)mappedData + sizeof(vertices), indices, sizeof(indices)); // put indices at offset of (uint8_t*)mappedData + sizeof(vertices)
		SDL_UnmapGPUTransferBuffer(_gpuDevice, bufferTransferBuffer);


		// command buffer for uploading

		SDL_GPUCommandBuffer* uploadCmdBuffer = SDL_AcquireGPUCommandBuffer(_gpuDevice);
		SDL_GPUCopyPass* copyPass = SDL_BeginGPUCopyPass(uploadCmdBuffer);


		{
			SDL_GPUTransferBufferLocation transferbufferloc;
			transferbufferloc.offset = 0;
			transferbufferloc.transfer_buffer = bufferTransferBuffer;

			SDL_GPUBufferRegion bufferRegion;
			bufferRegion.buffer = quadVertexBuffer;
			bufferRegion.offset = 0;
			bufferRegion.size = sizeof(vertices);

			SDL_UploadToGPUBuffer(copyPass, &transferbufferloc, &bufferRegion, false);
		}

		{
			SDL_GPUTransferBufferLocation transferbufferloc;
			transferbufferloc.offset = sizeof(vertices);
			transferbufferloc.transfer_buffer = bufferTransferBuffer;

			SDL_GPUBufferRegion bufferRegion;
			bufferRegion.buffer = quadIndicesBuffer;
			bufferRegion.offset = 0;
			bufferRegion.size = sizeof(indices);

			SDL_UploadToGPUBuffer(copyPass, &transferbufferloc, &bufferRegion, false);
		}


		SDL_EndGPUCopyPass(copyPass);
		SDL_SubmitGPUCommandBuffer(uploadCmdBuffer);
		SDL_ReleaseGPUTransferBuffer(_gpuDevice, bufferTransferBuffer);

		// this should be related to what camera is used, several cameras should be able to be used at once

		float aspectRatio = (float)windowWidth / (float)windowHeight;


		float orthoHeight = unitHeight / 2.0f;
		float orthoWidth = orthoHeight * aspectRatio;

		proj = glm::ortho(-orthoWidth, orthoWidth, -orthoHeight, orthoHeight, -1.0f, 1.0f);


		return 0;
	}


	void Renderer::draw() {

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
		colorTargetInfo.clear_color = { 0.0f, 0.0f, 0.0f, 1.0f };
		colorTargetInfo.load_op = SDL_GPU_LOADOP_CLEAR; // clear on load 
		colorTargetInfo.store_op = SDL_GPU_STOREOP_STORE; // write to memory

		// only works for 2d right now
		SDL_GPURenderPass* renderPass = SDL_BeginGPURenderPass(cmd, &colorTargetInfo, 1, nullptr);

		SDL_BindGPUGraphicsPipeline(renderPass, _spritePipeline);


		SDL_GPUBufferBinding vertexBufferBinding;
		vertexBufferBinding.buffer = quadVertexBuffer;
		vertexBufferBinding.offset = 0;

		SDL_BindGPUVertexBuffers(renderPass, 0, &vertexBufferBinding, 1);

		SDL_GPUBufferBinding indexBufferBinding;
		indexBufferBinding.buffer = quadIndicesBuffer;
		indexBufferBinding.offset = 0;
		SDL_BindGPUIndexBuffer(renderPass, &indexBufferBinding, SDL_GPU_INDEXELEMENTSIZE_16BIT);

		SDL_DrawGPUIndexedPrimitives(renderPass, 6, 1, 0, 0, 0);



		/*
		// this is not correct, fix this.
		for (auto& pair : RenderObjects) {
			pair.second->draw();
		}
		*/

		// cleanup

		SDL_EndGPURenderPass(renderPass);
		SDL_SubmitGPUCommandBuffer(cmd);

	}

	void Renderer::drawSprite(glm::mat4 model, Material& material)
	{
		/*
		int projLoc = defaultShader.getLocation("proj");
		int modelLoc = defaultShader.getLocation("model");

		float sizeX = (float)material.texture->width / pixels_per_unit;
		float sizeY = (float)material.texture->height / pixels_per_unit;

		glm::mat4 tempModel = glm::scale(model, glm::vec3(sizeX, sizeY, 1.0f));

		*/
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
		glViewport(0, 0, width, height);

		float aspectRatio = (float)windowWidth / (float)windowHeight;
		float orthoHeight = unitHeight / 2.0f;
		float orthoWidth = orthoHeight * aspectRatio;

		proj = glm::ortho(-orthoWidth, orthoWidth, -orthoHeight, orthoHeight, -1.0f, 1.0f);

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




}