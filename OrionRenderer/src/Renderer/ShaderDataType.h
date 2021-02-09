#pragma once
#include <vector>
#include <vulkan/vulkan.hpp>
namespace Orion {
	struct ShaderDataType {
	public:
		enum class type {number,vec2, vec3, vec4, };
		static size_t size(type Type) {
			switch (Type) {
			case type::vec2:
				return 2 * sizeof(float);
				break;
			case type::vec3:
				return 3 * sizeof(float);
				break;
			case type::vec4:
				return 4 * sizeof(float);
				break;
			case type::number:
				return sizeof(float);
				break;
			}
			return 0;
		}
		static VkFormat format(type Type) {
			switch (Type) {
			case type::vec2:
				return VK_FORMAT_R32G32_SFLOAT;
				break;
			case type::vec3:
				return VK_FORMAT_R32G32B32_SFLOAT;
				break;
			case type::vec4:
				return VK_FORMAT_R32G32B32A32_SFLOAT;
				break;
			case type::number:
				return VK_FORMAT_R32_SFLOAT;
				break;
			}
			return VK_FORMAT_UNDEFINED;
		}
	};
}