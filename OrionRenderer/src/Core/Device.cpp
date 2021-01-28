#include "../OrionBase.h"
#include "Log/Log.h"
#include "QueueFamilyIndex.h"
#include "Device.h"
#include "Queue.h"
#include <set>

Orion::Device::Device(GraphicsAdapter* graphicsAdapter, Surface& surface)
{
	VkDeviceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.enabledExtensionCount = 1;

	const char* extensions[] = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
	createInfo.ppEnabledExtensionNames = extensions;
	createInfo.pEnabledFeatures = 0;

	this->queueIndices = QueueFamilyIndices::FindQueueFamilies(graphicsAdapter,surface);

	std::set<uint32_t> uniqueQueueFamilies = { queueIndices.Graphics.value(), queueIndices.Present.value() };
	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos{};

	float queuePriority = 1.0f;
	for (uint32_t queueFamily : uniqueQueueFamilies) {
		VkDeviceQueueCreateInfo queueCreateInfo{};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = queueFamily;
		queueCreateInfo.queueCount = 1;
		queueCreateInfo.pQueuePriorities = &queuePriority;
		queueCreateInfos.push_back(queueCreateInfo);
	}

	createInfo.queueCreateInfoCount = (uint32_t)queueCreateInfos.size();
	createInfo.pQueueCreateInfos = queueCreateInfos.data();

	VkResult result = vkCreateDevice(*graphicsAdapter, &createInfo, nullptr, &device);
	OrionAssert(result == VK_SUCCESS, "Error %d", result);
	
	vkGetDeviceQueue(device, queueIndices.Graphics.value(), 0, &GraphicsQueue);
	vkGetDeviceQueue(device, queueIndices.Graphics.value(), 0, &PresentQueue);

}

void Orion::Device::Destroy(VkInstance instance)
{
	vkDestroyDevice(device, nullptr);
}
