#pragma once
#include <vulkan/vulkan.hpp>
#include "Device.h"
namespace Orion {
	class ShaderModule {
	public:
		ShaderModule() = default;
		ShaderModule(const ShaderModule&) = default;
		ShaderModule& operator=(const ShaderModule&) = default;
		
		void Create(Device* device, std::vector<uint8_t>& code);

		operator VkShaderModule& () { return vkShaderModule; }

		void Destroy(Device& device) { vkDestroyShaderModule(device,vkShaderModule,nullptr); }
	private:
		VkShaderModule vkShaderModule;
	};
}