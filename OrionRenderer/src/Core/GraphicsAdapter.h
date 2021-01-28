#pragma once
#include <vector>
#include <string_view>
#include <vulkan/vulkan.hpp>

namespace Orion {
	struct GraphicsAdapterType {
	public:
		GraphicsAdapterType() = default;
		GraphicsAdapterType(const GraphicsAdapterType&) = default;

		GraphicsAdapterType(uint32_t type) : type(type) {}

		operator uint32_t() { return type; }
		uint32_t type;
	};
	struct GraphicsAdapterSpecs {
	public:
		GraphicsAdapterSpecs() = default;
		GraphicsAdapterSpecs(const GraphicsAdapterSpecs&) = default;
		GraphicsAdapterSpecs(std::string Name, GraphicsAdapterType type) :Name(Name), type(type) {}
		GraphicsAdapterSpecs(std::string Name, GraphicsAdapterType type, std::vector<VkQueueFamilyProperties> queueProperties) 
				:Name(Name), type(type),queueProperties(queueProperties) {}
		std::string Name;
		GraphicsAdapterType type;
		std::vector<VkQueueFamilyProperties> queueProperties;
	};
	struct GraphicsAdapter {
	public:
		GraphicsAdapter() = default;
		GraphicsAdapter(const GraphicsAdapter&) = default;
		GraphicsAdapter(VkPhysicalDevice device,GraphicsAdapterSpecs specs):device(device),specs(specs){}

		VkPhysicalDevice device{};
		GraphicsAdapterSpecs specs{};

		operator VkPhysicalDevice() { return device; }

		static std::vector<GraphicsAdapter> GetGraphicsAdapters(VkInstance instanceHandle);
		static GraphicsAdapter SelectGraphicsAdapter(VkInstance instance,GraphicsAdapterType type);
	};

}