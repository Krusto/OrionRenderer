
#include "QueueFamilyIndex.h"

namespace Orion {
    QueueFamilyIndices Orion::QueueFamilyIndices::FindQueueFamilies(GraphicsAdapter* graphicsAdapter, Surface& surface)
    {
        QueueFamilyIndices indices;

        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(*graphicsAdapter, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(*graphicsAdapter, &queueFamilyCount, queueFamilies.data());

        int i = 0;
        for (const auto& queueFamily : queueFamilies) {
            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                indices.Graphics = (uint32_t&)i;
            }

            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(*graphicsAdapter, i, surface, &presentSupport);

            if (presentSupport) {
                indices.Present = (uint32_t&)i;
            }

            if (indices.IsComplete()) {
                break;
            }

            i++;
        }

        return indices;

    }
}