#pragma once
#include <string_view>
#include <array>
#include "Core/CommandPool.h"
#include "Core/Engine.h"
#include "Core/Queue.h"
namespace Orion {
	class Renderer {
	public:
		static void Init(WindowHandle window, std::vector<Extension>& ext, GraphicsAdapterType deviceType) {
			Orion::Engine::Init(window, ext, deviceType);
		}
		static void Destroy() { Orion::Engine::Destroy(); }
		static void cmdDraw(Command::Buffer* cmdBuffer, uint32_t vertexCount, uint32_t firstVertexOffset = 0);

		static uint32_t currentFrame;

		static void DrawFrame() {
			Orion::Engine::RenderFrame();
		}

		static void DrawFrame(Device* device,std::vector<Fence>& inFlightFences,
			std::vector<Fence>& imagesInFlight,
			std::vector<Semaphore>& imageAvailableSemahores,
			std::vector<Semaphore>& renderFinishedSemaphores,
			Swapchain* swapchain,
			std::vector<Command::Buffer>& cmdBuffers) {
			vkWaitForFences(*device, 1,&inFlightFences[currentFrame].handle(), VK_TRUE, UINT64_MAX);

			uint32_t imageIndex;
			vkAcquireNextImageKHR(*device,*swapchain, UINT64_MAX, imageAvailableSemahores[currentFrame], VK_NULL_HANDLE, &imageIndex);

			if (imagesInFlight[imageIndex].handle() != VK_NULL_HANDLE) {
				vkWaitForFences(*device, 1, &imagesInFlight[imageIndex].handle(), VK_TRUE, UINT64_MAX);
			}
			imagesInFlight[imageIndex].handle() = inFlightFences[currentFrame].handle();

			vkResetFences(*device, 1,&inFlightFences[currentFrame].handle());

			Semaphore waitSemaphores[] = { imageAvailableSemahores[imageIndex] };
			Semaphore signalSemaphores[] = { renderFinishedSemaphores[imageIndex] };

			std::vector<Semaphore> submitSemaphores = { waitSemaphores[0],signalSemaphores[0] };

			Queue(device->GraphicsQueue).Submit(submitSemaphores,&inFlightFences[currentFrame].handle(),cmdBuffers[currentFrame].handle());

			std::vector<Semaphore> presentSemahores = { imageAvailableSemahores[imageIndex],renderFinishedSemaphores[imageIndex]};
			Queue(device->PresentQueue).PresentKHR(presentSemahores,swapchain,imageIndex);

			vkQueueWaitIdle(device->PresentQueue);

			currentFrame = (currentFrame + 1) % 2;
		}
	};
}