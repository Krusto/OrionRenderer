#pragma once
#include <vulkan/vulkan.hpp>
#include "GraphicsAdapter.h"
#include "Device.h"
#include "Surface.h"
#include "QueueFamilyIndex.h"
namespace Orion {
	struct SwapchainSupportDetails {
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};

	class Swapchain {
	public:
		Swapchain() = default;
		Swapchain(const Swapchain&) = default;
		Swapchain& operator=(const Swapchain&) = default;

		void Create(Device* device, GraphicsAdapter* graphicsAdapter, Surface* surface, Size2i framebufferExtent);
		void Destroy(Device* device) {
			vkDestroySwapchainKHR(*device, swapchain, nullptr);
		}

		auto& GetImages() { return images; }
		auto& GetImageViews() { return imageViews; }

		SwapchainSupportDetails supportDetails;
		VkPresentModeKHR presentMode;
		VkSurfaceFormatKHR surfaceFormat;
		VkExtent2D size;

		std::vector<VkImage> images;
		std::vector<VkImageView> imageViews;

		operator VkSwapchainKHR& () { return swapchain; }
		VkSwapchainKHR swapchain;
	private:
		VkSurfaceFormatKHR ChooseSurfaceFormat(GraphicsAdapter* graphicsAdapter, Surface* surface);
		VkPresentModeKHR ChoosePresentMode(GraphicsAdapter* graphicsAdapter, Surface* surface);
		SwapchainSupportDetails FindSupportDetails(GraphicsAdapter* graphicsAdapter,Surface* surface);

	};

}