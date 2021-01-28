#pragma once
#include <vulkan/vulkan.hpp>
#include <vector>
namespace Orion {
	enum Extension {
		DEBUG_REPORT = 1,
		DEBUG_UTILS = 2,
		SWAPCHAIN_COLORSPACE = 3,
		KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2 = 4,
		KHR_GET_SURFACE_CAPABILITIES_2 = 5,
		KHR_SURFACE = 6,
		KHR_WIN32_SURFACE = 7
	};

	class Instance {
	public:
		static constexpr std::array<std::string_view, 7> ExtensionString{
			"VK_EXT_debug_report",
			"VK_EXT_debug_utils",
			"VK_EXT_swapchain_colorspace",
			"VK_KHR_get_physical_device_properties2",
			"VK_KHR_get_surface_capabilities2",
			"VK_KHR_surface",
			"VK_KHR_win32_surface",
		};
		static auto EnumerateSupportedExtensions() {
			return vk::enumerateInstanceExtensionProperties();
		}
		static std::vector<const char*> LoadExtensionNames(std::vector<Extension>& Extensions) {
			std::vector<const char*> extensionStrings;
			std::vector<vk::ExtensionProperties>  availableExt = vk::enumerateInstanceExtensionProperties();
		//	std::vector<vk::ExtensionProperties> availableExt;
			
			for (size_t i = 0; i < Extensions.size(); i++)
			{
				for (auto& ext : availableExt) {
					if (ext.extensionName == ExtensionString.at(Extensions[i] - 1)) {
						extensionStrings.emplace_back(	ExtensionString.at(Extensions[i] - 1).data());
					}
				}
			}
			return extensionStrings;
		}

	};
}