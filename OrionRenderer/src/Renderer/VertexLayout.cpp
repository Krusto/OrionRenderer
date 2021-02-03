#include "VertexLayout.h"

Orion::VertexLayout::VertexLayout(std::initializer_list<VertexAttribute> attributes)
	: mAttributes{attributes}
{
	for (auto& [name,type,offset] : mAttributes)
	{
		offset = mStride;
		mStride += (uint32_t)ShaderDataType::size(type);
	}

}
