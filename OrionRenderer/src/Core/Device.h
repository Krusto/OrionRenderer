#pragma once
#include <vulkan/vulkan.hpp>
#include "GraphicsAdapter.h"
#include "QueueFamilyIndex.h"
namespace Orion {
	class Device {
	public:
		Device() = default;
		Device(const Device&) = default;
		Device(GraphicsAdapter* graphicsAdapter, Surface& surface);

		void Destroy(VkInstance instance);
		operator VkDevice& () { return device; }
		VkDevice handle() { return device; }


		VkQueue GraphicsQueue = VK_NULL_HANDLE;
		VkQueue PresentQueue = VK_NULL_HANDLE;
		QueueFamilyIndices queueIndices;

	private:
		VkDevice device;
	};
}