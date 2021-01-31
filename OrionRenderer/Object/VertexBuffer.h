#pragma once
#include "VertexArray.h"
#include "../src/Core/Device.h"
#include "../src/Core/Log/Log.h"

namespace Orion {

	class VertexBuffer {
	public:
		VertexBuffer() = default;
		
		VertexBuffer(Device* device,VertexArray* vertexArray) {
			std::vector<VkVertexInputAttributeDescription> mAttrDescriptions;
			VkVertexInputBindingDescription mBindingDescription;

			uint32_t index = 0;
			mAttrDescriptions.resize(vertexArray->layout()->data().size());
			for (auto& attr : vertexArray->layout()->data()) {
				mAttrDescriptions[index].location = index;
				mAttrDescriptions[index].format = ShaderDataType::format(attr.type);
				mAttrDescriptions[index].offset = attr.offset;
				index++;
			}

			mBindingDescription = { 0,vertexArray->layout()->stride(),VK_VERTEX_INPUT_RATE_VERTEX };

			VkBufferCreateInfo bufferInfo{};
			bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
			bufferInfo.size = vertexArray->BufferSize();
			bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
			bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

			VkResult result = vkCreateBuffer(*device, &bufferInfo, nullptr, &mBuffer);
			OrionAssert(result == VK_SUCCESS, "Can not create vertex buffer!");

			OrionLog("Created Vertex buffer with size %d B", vertexArray->BufferSize());
		}
		void Create(Device* device, VertexArray* vertexArray) {
			if (mBuffer == VK_NULL_HANDLE) {
				std::vector<VkVertexInputAttributeDescription> mAttrDescriptions;
				VkVertexInputBindingDescription mBindingDescription;

				uint32_t index = 0;
				mAttrDescriptions.resize(vertexArray->layout()->data().size());
				for (auto& attr : vertexArray->layout()->data()) {
					mAttrDescriptions[index].location = index;
					mAttrDescriptions[index].format = ShaderDataType::format(attr.type);
					mAttrDescriptions[index].offset = attr.offset;
					index++;
				}

				mBindingDescription = { 0,vertexArray->layout()->stride(),VK_VERTEX_INPUT_RATE_VERTEX };

				VkBufferCreateInfo bufferInfo{};
				bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
				bufferInfo.size = vertexArray->BufferSize();
				bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
				bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

				VkResult result = vkCreateBuffer(*device, &bufferInfo, nullptr, &mBuffer);
				OrionAssert(result == VK_SUCCESS, "Can not create vertex buffer!");

				OrionLog("Created Vertex buffer with size %d B", vertexArray->BufferSize());
			}
			else {
				OrionLog("Buffer alrady created!");
			}
		}

		void Destroy(Device* device) {
			if (mBuffer != VK_NULL_HANDLE)
				vkDestroyBuffer(*device, mBuffer, nullptr);
		}
	private:
		VkBuffer mBuffer;
	};
}