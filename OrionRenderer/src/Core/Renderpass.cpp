#include "Renderpass.h"
#include "Log/Log.h"
void Orion::Renderpass::Create(Device* device, VkFormat* swapchainImageFormat)
{
    VkAttachmentDescription colorAttachment{};
    colorAttachment.format = *swapchainImageFormat;
    colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
    colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;  
    colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    VkAttachmentReference colorAttachmentRef{};
    colorAttachmentRef.attachment = 0;
    colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkSubpassDescription subpass{};
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &colorAttachmentRef;

    VkRenderPassCreateInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassInfo.attachmentCount = 1;
    renderPassInfo.pAttachments = &colorAttachment;
    renderPassInfo.subpassCount = 1;
    renderPassInfo.pSubpasses = &subpass;

    VkSubpassDependency dependency{};
    dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    dependency.dstSubpass = 0;
    dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.srcAccessMask = 0;
    dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

    renderPassInfo.dependencyCount = 1;
    renderPassInfo.pDependencies = &dependency;

    VkResult result = vkCreateRenderPass(*device, &renderPassInfo, nullptr, &renderpass);
    OrionAssert(result == VK_SUCCESS, "Can not create renderpass!");
}

void Orion::Renderpass::Begin(Orion::Command::Buffer* cmdBuffer,Orion::Swapchain* swapchain,Framebuffer* framebuffer , VkClearValue clearColor)
{
    VkRenderPassBeginInfo beginInfo = {};
    beginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    beginInfo.clearValueCount = 1;
    beginInfo.pClearValues = &clearColor;
    beginInfo.renderPass = renderpass;
    beginInfo.framebuffer = *reinterpret_cast<VkFramebuffer*>(framebuffer);
    beginInfo.renderArea = {0,0, swapchain->size.width, swapchain->size.height };
    
    vkCmdBeginRenderPass(*cmdBuffer, &beginInfo, VK_SUBPASS_CONTENTS_INLINE);
}

void Orion::Renderpass::End(Command::Buffer* cmdBuffer)
{
    vkCmdEndRenderPass(*cmdBuffer);
}
