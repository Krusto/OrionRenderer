#include <vector>
#include "OrionBase.h"
#include "Renderer.h"
#include "Core/Log/Log.h"
namespace Orion {

	uint32_t Renderer::currentFrame = 0;
	std::vector<Orion::VertexBuffer*> Renderer::rendererPool;

	void Renderer::cmdDraw(Command::Buffer* cmdBuffer, uint32_t vertexCount, uint32_t firstVertexOffset)
	{
		vkCmdDraw(*cmdBuffer,vertexCount, 1, firstVertexOffset, 0);
	}

}