#include "CommandPool.h"
#include "Log/Log.h"

void Orion::Command::Pool::Create(Device* device, uint32_t queueFamilyIndex)
{
	VkCommandPoolCreateInfo poolInfo{};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.queueFamilyIndex = queueFamilyIndex;

	OrionAssert(vkCreateCommandPool(*device, &poolInfo, nullptr, &commandPool) == VK_SUCCESS, "Can not create command poool!");
}

void Orion::Command::Buffer::Create(Device* device, Pool* commandPool, uint32_t level)
{
	VkCommandBufferAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = *commandPool;
	allocInfo.level = (VkCommandBufferLevel)level;
	allocInfo.commandBufferCount = 1;

	OrionAssert(vkAllocateCommandBuffers(*device, &allocInfo, &commandBuffer) == VK_SUCCESS,
		"Can not allocate command buffer!");
}

std::vector < Orion::Command::Buffer > Orion::Command::Buffer::AllocateCommandBuffers(uint32_t count, Device* device, Pool* commandPool, uint32_t level)
{
	std::vector<Buffer> output;

	for (size_t i = 0; i < count; i++)
	{
		output.push_back(Buffer());
		output.back().Create(device, commandPool, level);
	}

	return output;
}

void Orion::Command::Buffer::Begin()
{
		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = 0; // Optional
		beginInfo.pInheritanceInfo = nullptr; // Optional

		OrionAssert(vkBeginCommandBuffer(commandBuffer, &beginInfo) == VK_SUCCESS,
			"Failed to begin recording command buffer");
}

void Orion::Command::Buffer::End()
{
	OrionAssert(vkEndCommandBuffer(commandBuffer) == VK_SUCCESS,"Failed to record buffer!");
}
