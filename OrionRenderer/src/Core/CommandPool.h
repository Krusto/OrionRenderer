#pragma once
#include <vulkan/vulkan.hpp>
#include "Device.h"
namespace Orion {

	namespace Command {

		class Pool {
		public:
			Pool() = default;
			Pool(const Pool&) = default;
			Pool& operator=(const Pool&) = default;
			
			void Create(Device* device, uint32_t queueFamilyIndex);
			void Destroy(Device* device) { vkDestroyCommandPool(*device, commandPool, nullptr); }

			operator VkCommandPool& () { return commandPool; }

		private:
			VkCommandPool commandPool;
		};
		class Buffer {
		public:
			Buffer() = default;
			Buffer(const Buffer&) = default;
			Buffer& operator=(const Buffer&) = default;

			void Create(Device* device,Pool* commandPool, uint32_t level = VK_COMMAND_BUFFER_LEVEL_PRIMARY);
			static std::vector<Buffer> AllocateCommandBuffers(uint32_t count, Device* device, Pool* commandPool, uint32_t level = VK_COMMAND_BUFFER_LEVEL_PRIMARY);

			void Begin();
			void End();

			VkCommandBuffer& handle() { return commandBuffer; }

			operator VkCommandBuffer& () { return commandBuffer; }
		private:
			VkCommandBuffer commandBuffer;
		};
	}
}