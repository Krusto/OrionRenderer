#pragma once
#include <array>
#include <string_view>
#include "Log/Log.h"
#include <vector>
#include <vulkan/vulkan.hpp>
#include "Instance.h"
#include "GraphicsAdapter.h"
#include "Device.h"
#include "../Swapchain.h"
#include "../Window.h"
#include "Surface.h"
#include "GraphicsPipeline.h"
#include "Framebuffer.h"
#include "Semaphore.h"
#include "Fence.h"
#include "CommandPool.h"
namespace Orion {

	class Engine {
	public:
	
		static std::vector<const char*> EnabledExtensionNames;
		static GraphicsAdapter SelectedGraphicsCard;
		static std::vector<GraphicsAdapter> AvailableGraphicsCards;
		static Device device;
		static WindowHandle window;
		static Surface surface;
		static Swapchain swapchain;
		static Renderpass renderpass;
		static GraphicsPipeline graphicsPipeline;
		static std::vector<Framebuffer> SwapchainFramebuffers;
		static Command::Pool commandPool;
		static std::vector<Command::Buffer> commandBuffers;
		
		static std::vector<Semaphore> imageAvailableSemahores;
		static std::vector<Semaphore> renderFinishedSemaphores;

		static std::vector<Fence> inFlightFences;
		static std::vector<Fence> imagesInFlight;

		static void Init(WindowHandle window, std::vector<Extension> ext,GraphicsAdapterType deviceType);
		static void RenderFrame();
		static void EnableDebugCallback();
		static void Destroy();
	protected:
		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
			VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			VkDebugUtilsMessageTypeFlagsEXT messageType,
			const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
			void* pUserData) {

			if(messageSeverity & VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT){
				DebugError("validation layer: %s\n", pCallbackData->pMessage);
			}
			else {
				DebugLog("validation layer: %s\n", pCallbackData->pMessage);
			}
			return VK_FALSE;
		}

		static VkDebugUtilsMessengerEXT debugMessenger;
	};
}