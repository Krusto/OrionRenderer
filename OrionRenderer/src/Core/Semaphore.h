#pragma once
#include <vulkan\vulkan.hpp>
#include "Device.h"

namespace Orion {

	class Semaphore {
	public:
		Semaphore() = default;
		void Create(Device* device);
		void Destroy(Device* device);

		static std::vector<Semaphore> CreateMultiple(uint32_t count, Device* device);

		operator VkSemaphore& () { return semaphore; }
	private:
		VkSemaphore semaphore;
	};
}