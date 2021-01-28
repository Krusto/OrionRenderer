#pragma once

#include "../OrionBase.h"
#include "../Util/Optional.h"
#include "Surface.h"
#include "GraphicsAdapter.h"
#include "Device.h"
#include "CommandPool.h"
#include "Semaphore.h"
#include <cstdint>
#include "QueueFamilyIndex.h"
#include "../Swapchain.h"
#include "CommandPool.h"
namespace Orion {

	class Queue {
	public:
		Queue() = default;
		Queue(const Queue&) = default;
		Queue& operator=(const Queue&) = default;
		Queue(VkQueue& queue) {
			this->queue = queue;
		}


		void Get(Device* device, uint32_t index,uint32_t Type);
		void Submit(std::vector<Semaphore>& semaphores,VkFence* fence,VkCommandBuffer cmdBuffer);
		void PresentKHR(std::vector<Semaphore>& semaphores, Swapchain* swapchain, uint32_t imageIndex);

		uint32_t index{};
		uint32_t type{};

		enum QueueT : unsigned int{
			Graphics = 1,
			Compute = 2,
			Transfer = 4,
			Present = 5,
			SparceBinding = 8,
			Protected = 0x10,
			Max = 0x7FFFFFFF
		};
	private:
		VkQueue queue = VK_NULL_HANDLE;
	};
}