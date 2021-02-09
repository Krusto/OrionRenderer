#include "Log/Log.h"
#include "Swapchain.h"
#include "Queue.h"
#include "ImageView.h"

namespace Orion {
    void Swapchain::Create(Device* device,GraphicsAdapter* graphicsAdapter, Surface* surface, Size2i framebufferExtent)
    {
        this->supportDetails = FindSupportDetails(graphicsAdapter, surface);
        this->presentMode = ChoosePresentMode(graphicsAdapter, surface);
        this->surfaceFormat = ChooseSurfaceFormat(graphicsAdapter, surface);
        this->size = { framebufferExtent.width,framebufferExtent.height };


        VkSwapchainCreateInfoKHR createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        createInfo.minImageCount = this->supportDetails.capabilities.minImageCount;
        createInfo.imageFormat = this->surfaceFormat.format;
        createInfo.imageColorSpace = this->surfaceFormat.colorSpace;
        createInfo.presentMode = this->presentMode;
        createInfo.imageExtent = this->size;
        createInfo.imageArrayLayers = 1;
        createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

        QueueFamilyIndices indices = QueueFamilyIndices::FindQueueFamilies(graphicsAdapter,*surface);
        uint32_t queueFamilyIndices[] = { indices.Graphics.value(), indices.Present.value() };

        if (indices.Graphics.value() != indices.Present.value()) {
            createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            createInfo.queueFamilyIndexCount = 2;
            createInfo.pQueueFamilyIndices = queueFamilyIndices;
        }
        else {
            createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
            createInfo.queueFamilyIndexCount = 0; // Optional
            createInfo.pQueueFamilyIndices = nullptr; // Optional
        }

        createInfo.preTransform = this->supportDetails.capabilities.currentTransform;
        createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        createInfo.presentMode = this->presentMode;
        createInfo.clipped = VK_TRUE;
        createInfo.surface = *surface;

        VkResult result = vkCreateSwapchainKHR(*device, &createInfo, nullptr, &this->swapchain);
        OrionAssert(result == VK_SUCCESS, "Can not Create Swapchain Error :%d", result);

        uint32_t count;

        vkGetSwapchainImagesKHR(*device, this->swapchain, &count, nullptr);
        this->images.resize(count);
        vkGetSwapchainImagesKHR(*device, this->swapchain, &count, this->images.data());

        OrionLog("Using %i swapchain images!", count);

        this->imageViews.resize(count);
        for (uint32_t i = 0; i < count; i++)
        {
            this->imageViews[i] = *ImageView(device,this->images[i], this->surfaceFormat.format);
        }
    }
    VkSurfaceFormatKHR Swapchain::ChooseSurfaceFormat(GraphicsAdapter* graphicsAdapter, Surface* surface)
    {
        VkSurfaceFormatKHR format = this->supportDetails.formats[0];

        std::for_each(this->supportDetails.formats.begin(), this->supportDetails.formats.end(),
            [&r = format](const VkSurfaceFormatKHR& current) {
                if (current.format == VK_FORMAT_B8G8R8A8_SRGB && current.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
                    r = current;
                }
            });

        return format;
    }
    VkPresentModeKHR Swapchain::ChoosePresentMode(GraphicsAdapter* graphicsAdapter, Surface* surface)
    {
        OrionLog("Available Present Modes: ")
        for (auto& mode : this->supportDetails.presentModes) {
            OrionLog("%>4%i", mode);
        }
        VkPresentModeKHR output = this->supportDetails.presentModes[0];

        std::for_each(this->supportDetails.presentModes.begin(), this->supportDetails.presentModes.end(),
            [&r = output](const VkPresentModeKHR& current) {
                if (current == VK_PRESENT_MODE_MAILBOX_KHR) {
                    r = current;
                }
            });

        return output;
    }
    SwapchainSupportDetails Orion::Swapchain::FindSupportDetails(GraphicsAdapter* graphicsAdapter,Surface* surface)
    {
        SwapchainSupportDetails details;

        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(*graphicsAdapter, *surface, &details.capabilities);

        uint32_t formatCount;
        vkGetPhysicalDeviceSurfaceFormatsKHR(*graphicsAdapter, *surface, &formatCount, nullptr);

        if (formatCount != 0) {
            details.formats.resize(formatCount);
            vkGetPhysicalDeviceSurfaceFormatsKHR(*graphicsAdapter, *surface, &formatCount, details.formats.data());
        }

        uint32_t presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(*graphicsAdapter, *surface, &presentModeCount, nullptr);

        if (presentModeCount != 0) {
            details.presentModes.resize(presentModeCount);
            vkGetPhysicalDeviceSurfacePresentModesKHR(*graphicsAdapter, *surface, &presentModeCount, details.presentModes.data());
        }

        return details;
    }

}