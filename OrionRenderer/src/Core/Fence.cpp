#include "Fence.h"
#include "Log/Log.h"

void Orion::Fence::Create(Device* device, uint32_t flags)
{
	VkFenceCreateInfo createInfo = { VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,nullptr,flags };
	
	VkResult result = vkCreateFence(*device, &createInfo, nullptr, &fence);
	OrionAssert(result == VK_SUCCESS, "Can not create fence!");
}

void Orion::Fence::Destroy(Device* device)
{
	vkDestroyFence(*device, fence, nullptr);
}

std::vector<Orion::Fence> Orion::Fence::CreateMultiple(uint32_t count, Device* device, uint32_t flags)
{
	std::vector<Fence> output;

	for (size_t i = 0; i < count; i++)
	{
		output.push_back(Fence());
		output.back().Create(device,flags);
	}

	return output;
}
