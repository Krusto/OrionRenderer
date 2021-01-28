#pragma once
#include <vulkan/vulkan.hpp>
#include "Device.h"
#include "Renderpass.h"
#include "ImageView.h"
namespace Orion {
	class Framebuffer {
	public:
		Framebuffer() = default;
		Framebuffer(const Framebuffer&) = default;
		Framebuffer& operator=(const Framebuffer&) = default;

		void Create(Device* device, Renderpass* renderpass,Size2i size, VkImageView* imageView);
		void Destroy(Device* device) {
			vkDestroyFramebuffer(*device, framebuffer, nullptr);
		}
		operator VkFramebuffer& () { return framebuffer; }

	private:
		VkFramebuffer framebuffer;
	};
}