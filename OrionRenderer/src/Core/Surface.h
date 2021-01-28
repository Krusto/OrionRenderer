#pragma once
#include <vulkan/vulkan.hpp>
#include "../Window.h"
namespace Orion {
	class Surface {
	public:
		Surface() = default;
		Surface(const Surface&) = default;
		Surface(VkInstance instance,WindowHandle handle);
		~Surface();

		void Destroy(VkInstance instance);
		Surface& operator=(const Surface&) = default;
		operator VkSurfaceKHR& () { return surface; }

		VkSurfaceFormatKHR format;
		VkPresentModeKHR presentmode;

	private:
		VkSurfaceKHR surface;
	};
}