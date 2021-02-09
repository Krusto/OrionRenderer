#pragma once
#include "../Window.h"
#include <vulkan/vulkan.hpp>
struct Viewport {
public:
	Viewport() = default;
	Viewport(const Viewport&) = default;
	Viewport& operator=(const Viewport&) = default;
	Viewport(Size2i size) :size(size) {
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = (float)size.width;
		viewport.height = (float)size.height;
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;
	};

	operator VkViewport& () {
		return viewport;
	}
	
	VkExtent2D Size() {
		return { size.width, size.height};
	}

	Size2i size;
	VkViewport viewport{};
};