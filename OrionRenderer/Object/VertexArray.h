#pragma once
#include <vector>
#include "Vertex.h"
#include "VertexLayout.h"
namespace Orion {
	class VertexArray {
	public:
		VertexArray() = default;
		VertexArray(std::vector<Vertex>* data, VertexLayout* layout) {
			this->mVertexData = data;
			mLayout = layout;
		}

		size_t count() { return mVertexData->size(); }
		size_t BufferSize() { return mVertexData->size() * mLayout->stride(); }

		std::vector<Vertex>* data() { return mVertexData; }
		const std::vector<Vertex>* data() const{ return mVertexData; }


		Vertex& operator[](std::size_t index) { return mVertexData->at(index); }
		const Vertex& operator[](std::size_t index) const { return mVertexData->at(index); };

		VertexLayout* layout() { return mLayout; }
	private:
		std::vector<Vertex>* mVertexData;
		VertexLayout* mLayout;
	};
}