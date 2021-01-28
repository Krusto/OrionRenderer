#include "Framebuffer.h"
#include "Log/Log.h"

void Orion::Framebuffer::Create(Device* device, Renderpass* renderpass, Size2i size, VkImageView* imageView)
{

    VkFramebufferCreateInfo framebufferInfo{};
    framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebufferInfo.renderPass = *renderpass;
    framebufferInfo.attachmentCount = 1;
    framebufferInfo.pAttachments = imageView;
    framebufferInfo.width = size.width;
    framebufferInfo.height = size.height;
    framebufferInfo.layers = 1;

    VkResult result = vkCreateFramebuffer(*device, &framebufferInfo, nullptr, &framebuffer);
    OrionAssert(result == VK_SUCCESS, "Can not create framebuffer!");

}
