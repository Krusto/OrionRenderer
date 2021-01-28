#pragma once
#include "./Util/File.h"
#include "Core/ShaderModule.h"
namespace Orion {
	enum ShaderType {
		None = 0,
		Vertex = 1,
		Fragment = 2,
		Compute = 4
	};
	class Shader {
	public:
		Shader()=default;
		Shader(const Shader&) = default;
		Shader& operator=(const Shader&) = default;
		Shader(Device* device,std::string_view Name,std::string_view path,ShaderType type);
		void DestroyModule(Device* device);

		void Compile();
		void Reload();
		
		std::vector<uint8_t>& data() { return ShaderFile.data; }

		std::string_view ShaderPath;
		std::string_view Name;
		Util::File ShaderFile;
		ShaderType type;
		ShaderModule shaderModule;
	};
}
