#pragma once
#include <vector>
namespace Orion {
	struct Vertex {
	public:
		Vertex() = default;
		float Position[3] = { 0,0,0 };
		float Color[3] = { 0,0,0 };
	};
}