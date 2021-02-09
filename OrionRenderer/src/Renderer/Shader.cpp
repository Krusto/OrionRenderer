#include "Shader.h"
#include <filesystem>
#ifdef _WIN32
#include <Windows.h>
#elif __linux__
#error not supported yet!
#endif
Orion::Shader::Shader(Device* device,std::string_view Name, std::string_view path,ShaderType type)
	:ShaderPath(path),Name(Name),type(type)
{
	Compile();

	shaderModule.Create(device, this->ShaderFile.data);

	OrionLog("Created shader with name: %s path: %s",Name.data(),path.data());
}

void Orion::Shader::DestroyModule(Device* device)
{
	shaderModule.Destroy(*device);
}

void Orion::Shader::Compile()
{
	std::string FullShaderPath = std::filesystem::absolute(std::string(ShaderPath.data()) + std::string(Name.data())).generic_string();
	std::string compilerPath = std::filesystem::absolute("./bin/").generic_string()+"glslc";
#ifdef _WIN32
	
	OrionLog("Executed Command: \n\r %>4 %s",(compilerPath + " " + FullShaderPath + " -o " + FullShaderPath + ".spv").c_str());
	system(("cmd.exe /c "+compilerPath + " " + FullShaderPath + " -o " + FullShaderPath + ".spv").c_str());
#elif __linux__
#error not supported yet!
#endif
	ShaderFile.Open((std::string(FullShaderPath.data()) + ".spv").c_str(), Orion::Util::FileDataType::Binary, Orion::Util::FileOperationFlags::Read);

}
void Orion::Shader::Reload()
{
	ShaderFile.Free();
	
	std::string FullShaderPath = std::string(ShaderPath.data()) + std::string(Name.data());
	ShaderFile.Open((std::string(FullShaderPath.data()) + ".spv").c_str(), Orion::Util::FileDataType::Binary, Orion::Util::FileOperationFlags::Read);


}

