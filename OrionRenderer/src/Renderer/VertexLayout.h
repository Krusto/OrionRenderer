#pragma once
#include <vector>
#include "Vertex.h"
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
		VertexLayout(const VertexLayout&) = default;

		std::uint32_t stride() { return mStride; }

		std::vector<VertexAttribute> mAttributes;
		std::uint32_t mStride{};

		VertexLayout& operator=(const VertexLayout& other) = default;

	};
}