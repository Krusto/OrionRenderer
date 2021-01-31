#pragma once
#include <vulkan\vulkan.hpp>
#include "ShaderDataType.h"

namespace Orion {
	struct VertexAttribute {
	public:
		std::string_view name{};
		ShaderDataType::type type;
		uint32_t offset{};
	};

	class VertexLayout {
	public:
		VertexLayout() = default;
		VertexLayout(std::initializer_list<VertexAttribute> attributes);

		std::uint32_t stride() const { return mStride; }
		std::vector<VertexAttribute>& data() { return mAttributes; }
		std::vector<VertexAttribute>::iterator begin() { return mAttributes.begin(); }
		std::vector<VertexAttribute>::iterator end() { return mAttributes.end(); }
		std::vector<VertexAttribute>::const_iterator cbegin() { return mAttributes.cbegin(); }
		std::vector<VertexAttribute>::const_iterator cend() { return mAttributes.cend(); }


		VertexAttribute& operator[](std::size_t index) { return mAttributes[index]; }
		const VertexAttribute& operator[](std::size_t index) const { return mAttributes[index]; };
	private:

		std::uint32_t mStride{};
		std::vector<VertexAttribute> mAttributes;
	};
}