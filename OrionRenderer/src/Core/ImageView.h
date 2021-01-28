#pragma once
#include <vulkan/vulkan.hpp>
#include "Device.h"
namespace Orion {
	class ImageView {
	public:
		ImageView() = default;
		ImageView(const ImageView&) = default;
		ImageView(Device* device,VkImage& image, VkFormat format);
		ImageView& operator=(const ImageView&) = default;
		operator VkImageView* () { return &this->imageView; };
	private:
		VkImageView imageView;
	};
}