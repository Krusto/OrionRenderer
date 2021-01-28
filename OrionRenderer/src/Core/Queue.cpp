#include "Queue.h"
#include "Device.h"
#include "Log/Log.h"
#include "CommandPool.h"
namespace Orion {
	void Queue::Get(Device* device, uint32_t index, uint32_t Type)
	{
		type = Type;
		this->index = index;
		vkGetDeviceQueue(*device, index, 0, &queue);
	}

	void Queue::Submit(std::vector<Semaphore>& semaphores,VkFence* fence,VkCommandBuffer cmdBuffer)
	{
		VkSubmitInfo submitInfo{};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

		VkSemaphore waitSemaphores[] = { semaphores[0] };
		VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
		submitInfo.waitSemaphoreCount = 1;
		submitInfo.pWaitSemaphores = waitSemaphores;
		submitInfo.pWaitDstStageMask = waitStages;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers =&cmdBuffer;

		VkSemaphore signalSemaphores[] = { semaphores[1] };
		submitInfo.signalSemaphoreCount = 1;
		submitInfo.pSignalSemaphores = signalSemaphores;

		OrionAssert(vkQueueSubmit(queue, 1, &submitInfo,*fence) == VK_SUCCESS, "Failed to submit draw command buffer!");
	}

	void Queue::PresentKHR(std::vector<Semaphore>& semaphores, Swapchain* swapchain, uint32_t imageIndex)
	{
		VkSemaphore waitSemaphores[] = { semaphores[0] };
		VkSemaphore signalSemaphores[] = { semaphores[1] };

		VkPresentInfoKHR presentInfo{};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = signalSemaphores;

		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = reinterpret_cast<VkSwapchainKHR*>(&swapchain->swapchain);
		presentInfo.pImageIndices = &imageIndex;
		presentInfo.pResults = nullptr; // Optional

		vkQueuePresentKHR(queue, &presentInfo);
	}

	

}