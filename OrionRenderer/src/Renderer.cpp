#include <vector>
#include "Renderer.h"
#include "OrionBase.h"
#include "Core/Log/Log.h"
namespace Orion {

	void Renderer::Init()
	{
			

	}

	uint32_t Renderer::currentFrame = 0;

	void Renderer::cmdDraw(Command::Buffer* cmdBuffer, uint32_t vertexCount, uint32_t firstVertexOffset)
	{
		vkCmdDraw(*cmdBuffer,vertexCount, 1, firstVertexOffset, 0);
	}

}