#include <vulkan\vulkan.hpp>
#include "Log/Log.h"
#include "../OrionBase.h"
#include "Instance.h"
#include "Engine.h"
#include "GraphicsAdapter.h"
#include <iostream>
#include <bitset>
#include "Device.h"
#include "../Swapchain.h"
#include "../Util/File.h"
#include "../Shader.h"
#include "Framebuffer.h"
#include "../Renderer.h"
VkDebugUtilsMessengerEXT					Orion::Engine::debugMessenger{};
std::vector<const char*>					Orion::Engine::EnabledExtensionNames;
Orion::GraphicsAdapter						Orion::Engine::SelectedGraphicsCard;
std::vector<Orion::GraphicsAdapter>			Orion::Engine::AvailableGraphicsCards;
Orion::Device								Orion::Engine::device;
WindowHandle								Orion::Engine::window;
Orion::Surface								Orion::Engine::surface;
Orion::Swapchain							Orion::Engine::swapchain;
Orion::Renderpass							Orion::Engine::renderpass;
Orion::GraphicsPipeline						Orion::Engine::graphicsPipeline;
std::vector<Orion::Framebuffer>				Orion::Engine::SwapchainFramebuffers;
Orion::Command::Pool						Orion::Engine::commandPool;
std::vector<Orion::Command::Buffer>			Orion::Engine::commandBuffers;
std::vector<Orion::Semaphore>				Orion::Engine::imageAvailableSemahores;
std::vector<Orion::Semaphore>				Orion::Engine::renderFinishedSemaphores;
std::vector<Orion::Fence>					Orion::Engine::inFlightFences;
std::vector<Orion::Fence>					Orion::Engine::imagesInFlight;

void Orion::Engine::Init(WindowHandle window,std::vector<Orion::Extension> ext, GraphicsAdapterType deviceType)
{
	Orion::Engine::window = window;
	
	auto extensions = vk::enumerateInstanceExtensionProperties();
	DebugLog("Supported Extensions:");
	for (auto& extension : extensions) {
		DebugLog("%>4%s", extension.extensionName);
	}

	std::vector<const char*> loadedExtensions = Instance::LoadExtensionNames(ext);
	DebugLog("Loaded Extensions:");
	for (auto& extension : loadedExtensions)
		DebugLog("%>4%s", std::string(extension).c_str());

	std::vector<const char*> layers{
		"VK_LAYER_KHRONOS_validation",
	};

	VkInstanceCreateInfo instanceCreateInfo{};
	instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceCreateInfo.enabledLayerCount = (uint32_t)layers.size();
	instanceCreateInfo.ppEnabledLayerNames = layers.data();
	instanceCreateInfo.enabledExtensionCount = (uint32_t)loadedExtensions.size();
	instanceCreateInfo.ppEnabledExtensionNames = loadedExtensions.data();

	VkApplicationInfo applicationInfo{};
	applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	applicationInfo.apiVersion = VK_MAKE_VERSION(1,1,126);
	applicationInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	applicationInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	applicationInfo.pEngineName = "Orion";
	applicationInfo.pApplicationName = "None";

	instanceCreateInfo.pApplicationInfo = &applicationInfo;

	VkResult result = vkCreateInstance(&instanceCreateInfo, nullptr, &Orion::instance);

	OrionAssert((result == VK_SUCCESS),"%i", result);

	EnableDebugCallback();

	surface = Surface(instance, window);

	Orion::Engine::SelectedGraphicsCard = Orion::GraphicsAdapter::SelectGraphicsAdapter(Orion::instance, deviceType);
	OrionLog("Selected adapter : %s type : %i",SelectedGraphicsCard.specs.Name.c_str(),SelectedGraphicsCard.specs.type );
	Orion::Engine::AvailableGraphicsCards = Orion::GraphicsAdapter::GetGraphicsAdapters(Orion::instance);

	auto& adapters = Orion::Engine::AvailableGraphicsCards;
	for (auto& adapter : adapters) {
		OrionLog("%s :", adapter.specs.Name.c_str());
		for (auto& property : adapter.specs.queueProperties) {
			OrionLog("%>4Queue Count : %i Flags: %i", property.queueCount, std::bitset<8>(property.queueFlags));
		}
	}

	device = Device(&Engine::SelectedGraphicsCard,surface);

	swapchain.Create(&device,&Engine::SelectedGraphicsCard, &surface,window->GetWindowExtent());

	Orion::Shader vertShader(&device,"shader.vert","./assets/shaders/",Orion::ShaderType::Vertex);
	Orion::Shader fragShader(&device,"shader.frag","./assets/shaders/",Orion::ShaderType::Fragment);

	renderpass.Create(&device, &swapchain.surfaceFormat.format);

	Viewport viewport( { swapchain.size.width,swapchain.size.height });

	graphicsPipeline.Create(&device, &renderpass, &viewport, VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
		&vertShader.shaderModule, &fragShader.shaderModule, true);

	vertShader.DestroyModule(&device);
	fragShader.DestroyModule(&device);


	for (auto& imageView : swapchain.GetImageViews()) {
		SwapchainFramebuffers.push_back(Framebuffer());
		SwapchainFramebuffers.back().Create(&device, &renderpass, viewport.size, &imageView);
	}

	commandPool.Create(&device,device.queueIndices.Graphics.value());
	commandBuffers = Command::Buffer::AllocateCommandBuffers((uint32_t)SwapchainFramebuffers.size(),&device,&commandPool, VK_COMMAND_BUFFER_LEVEL_PRIMARY);

	uint32_t i = 0;
	for (auto& cmdBuffer : commandBuffers) {
		cmdBuffer.Begin();

		renderpass.Begin(&cmdBuffer, &swapchain, &SwapchainFramebuffers[i], { 0,0,0,1 });

		graphicsPipeline.Bind(&cmdBuffer);
		Renderer::cmdDraw(&cmdBuffer, 3, 0);

		renderpass.End(&cmdBuffer);

		cmdBuffer.End();
		i++;
	}

	imageAvailableSemahores = Semaphore::CreateMultiple(2, &device);
	renderFinishedSemaphores = Semaphore::CreateMultiple(2, &device);
	
	imagesInFlight.resize(swapchain.images.size());

	for (auto& fence : imagesInFlight) {
		fence = VK_NULL_HANDLE;
	}

	inFlightFences = Fence::CreateMultiple(2, &device, VK_FENCE_CREATE_SIGNALED_BIT);

}
void Orion::Engine::RenderFrame()
{
	Renderer::DrawFrame(&device,
		inFlightFences, imagesInFlight, imageAvailableSemahores, renderFinishedSemaphores, &swapchain, commandBuffers);
}
void Orion::Engine::EnableDebugCallback()
{
	VkDebugUtilsMessengerCreateInfoEXT createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	createInfo.pfnUserCallback = Engine::debugCallback;
	createInfo.pUserData = nullptr; // Optional

	auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
	if (func != nullptr) {
		func(Orion::instance, &createInfo, nullptr, &Engine::debugMessenger);
	}
	else {
		OrionLog("Error extension not present!");
	}

}
void Orion::Engine::Destroy()
{

	for (auto& fence : inFlightFences)
		fence.Destroy(&device);
	for (auto& semaphore : imageAvailableSemahores) 
		semaphore.Destroy(&device);
	for (auto& semaphore : renderFinishedSemaphores)
		semaphore.Destroy(&device);

	commandPool.Destroy(&device);

	for (auto& framebuffer : SwapchainFramebuffers)
		framebuffer.Destroy(&device);

	graphicsPipeline.Destroy(&device);
	renderpass.Destroy(&device);

	for (auto& imageView : swapchain.GetImageViews())
		vkDestroyImageView(device, imageView, nullptr);

	swapchain.Destroy(&device);
	surface.Destroy(instance);
	device.Destroy(instance);

	auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
	if (func != nullptr) {
		func(Orion::instance,Engine::debugMessenger,nullptr);
	}
	else {
		OrionLog("Error extension not present!");
	}

	vkDestroyInstance(Orion::instance, nullptr);
}
