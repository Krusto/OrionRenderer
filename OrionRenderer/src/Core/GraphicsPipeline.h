#pragma once
#include <vulkan\vulkan.hpp>
#include "Device.h"
#include "ShaderModule.h"
#include "../Renderer/Viewport.h"
#include "Renderpass.h"
#include "CommandPool.h"
namespace Orion {

	class GraphicsPipeline {
	public:
		GraphicsPipeline() = default;
		GraphicsPipeline(const GraphicsPipeline&) = default;
		GraphicsPipeline& operator=(const GraphicsPipeline&) = default;

		void Create(Device* device, Renderpass* renderpass, Viewport* viewport, VkPrimitiveTopology topology, ShaderModule* vertShaderModule, ShaderModule* fragShaderModule, bool blendEnable = false);

		void Bind(Command::Buffer* cmdBuffer){ vkCmdBindPipeline(*cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,pipeline); }

		void Destroy(Device* device) {
			vkDestroyPipeline(*device, pipeline, nullptr);
			vkDestroyPipelineLayout(*device, pipelineLayout, nullptr);
		}

		operator VkPipeline& () { return pipeline; }
	private:
		VkPipelineLayout pipelineLayout;
		VkPipeline pipeline;
	};
}