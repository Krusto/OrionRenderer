#pragma once
#include <vulkan/vulkan.hpp>
#include "Device.h"
namespace Orion {
	class Fence {
	public:
		Fence() = default;	
		Fence(VkFence fence) { this->fence = fence; }
		void Create(Device* device, uint32_t flags = 0);
		void Destroy(Device* device);

		static std::vector<Fence> CreateMultiple(uint32_t count,Device* device, uint32_t flags=0);
		operator VkFence* () { return &fence; }
		
		VkFence& handle() { return fence; }

		Fence& operator=(const Fence& other) { this->fence = other.fence; return *this; }
	private:
		VkFence fence;
	};
}