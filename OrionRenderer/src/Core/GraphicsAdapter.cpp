#include "GraphicsAdapter.h"
#include "Log/Log.h"

namespace Orion {
	std::vector<GraphicsAdapter> GraphicsAdapter::GetGraphicsAdapters(VkInstance instanceHandle)
	{
		std::vector<GraphicsAdapter> output;
		uint32_t deviceCount = 0;
		VkResult result;

		result = vkEnumeratePhysicalDevices(instanceHandle, &deviceCount, nullptr);
		OrionAssert(result == VK_SUCCESS, "Can not get graphics adapter count!");

		std::vector<VkPhysicalDevice> physicalDevices(deviceCount);
		result = vkEnumeratePhysicalDevices(instanceHandle, &deviceCount, physicalDevices.data());
		OrionAssert(result == VK_SUCCESS, "Can not enumerate physical devices!");

		VkPhysicalDeviceProperties prop;
		for (auto& device : physicalDevices)
		{
			vkGetPhysicalDeviceProperties(device, &prop);
			uint32_t count;
			vkGetPhysicalDeviceQueueFamilyProperties(device, &count, nullptr);
			std::vector<VkQueueFamilyProperties> queueProps(count);
			vkGetPhysicalDeviceQueueFamilyProperties(device, &count, queueProps.data());

			GraphicsAdapterSpecs specs{};
			specs.Name = std::string(prop.deviceName);
			specs.type = prop.deviceType;
			specs.queueProperties = queueProps;

			output.push_back(GraphicsAdapter(device, specs));
		}

		return output;
	}

	GraphicsAdapter GraphicsAdapter::SelectGraphicsAdapter(VkInstance instance, GraphicsAdapterType type)
	{
		auto devices = GetGraphicsAdapters(instance);

		for (auto& device : devices) {
			if (device.specs.type == type) {
				return device;
			}
		}

		return devices[0];
	}
}