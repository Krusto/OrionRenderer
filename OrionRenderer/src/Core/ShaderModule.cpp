#include "ShaderModule.h"
#include "Log/Log.h"

namespace Orion {
	void ShaderModule::Create(Device* device, std::vector<uint8_t>& code)
	{
		VkShaderModuleCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = (size_t)code.size();
		createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

		VkResult result = vkCreateShaderModule(*device, &createInfo, nullptr, &this->vkShaderModule);

		OrionAssert(result == VK_SUCCESS, "Can not create Shader Module!");
	}

}