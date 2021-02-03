#pragma once
#include <vulkan/vulkan.hpp>
#include "Device.h"
#include "Swapchain.h"
#include "CommandPool.h"
using Framebuffer = void;
namespace Orion {
	class Renderpass {
	public:
		Renderpass() = default;
		Renderpass(const Renderpass&) = default;
		Renderpass& operator=(const Renderpass&) = default;

		void Create(Device* device, VkFormat* swapchainImageFormat);
		void Destroy(Device* device) {if (device != nullptr) { vkDestroyRenderPass(device->handle(), renderpass, nullptr); }}

		void Begin(Command::Buffer* cmdBuffer,Swapchain* swapchain, Framebuffer* framebuffer, VkClearValue clearColor);
		void End(Command::Buffer* cmdBuffer);

		operator VkRenderPass& () { return renderpass; }
	private:
		VkRenderPass renderpass = VK_NULL_HANDLE;
	};
}