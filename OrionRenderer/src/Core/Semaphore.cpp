#include "Semaphore.h"
#include "Log/Log.h"

void Orion::Semaphore::Create(Device* device)
{
    VkSemaphoreCreateInfo createInfo = {VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,nullptr,0};

    VkResult result = vkCreateSemaphore(*device, &createInfo, nullptr, &semaphore);
    OrionAssert(result == VK_SUCCESS, "Can not create semaphore!");

}

void Orion::Semaphore::Destroy(Device* device)
{
    vkDestroySemaphore(*device, semaphore, nullptr);
}

std::vector<Orion::Semaphore> Orion::Semaphore::CreateMultiple(uint32_t count, Device* device)
{
    std::vector<Semaphore> output;

    for (size_t i = 0; i < count; i++)
    {
        output.push_back(Semaphore());
        output.back().Create(device);
    }

    return output;
}
