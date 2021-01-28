#define GLFW_EXPOSE_NATIVE_WIN32
#define VK_USE_PLATFORM_WIN32_KHR "VK_KHR_Win32_surface"

#include "Surface.h"
#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include "Log/Log.h"

Orion::Surface::Surface(VkInstance instance,WindowHandle handle)
{
	VkWin32SurfaceCreateInfoKHR createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	createInfo.hwnd = glfwGetWin32Window(handle->getHandle());
	createInfo.hinstance = GetModuleHandle(nullptr);

	VkResult result = vkCreateWin32SurfaceKHR(instance, &createInfo, nullptr, &surface);

	OrionAssert(result == VK_SUCCESS, "Can not create Win32 Surface!!!");

}

Orion::Surface::~Surface()
{
}

void Orion::Surface::Destroy(VkInstance instance)
{
	vkDestroySurfaceKHR(instance, surface, nullptr);
}
