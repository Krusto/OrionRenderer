#include "File.h"
#include <filesystem>
#include <fstream>
#include "../Core/Log/Log.h"

Orion::Util::File::File(const char* path, FileDataType dataType,FileOperationFlags fileOperationFlags)
{
	OrionAssert(std::filesystem::exists(path), "File %s does not exist", path);
	
	this->dataType = dataType;
	this->fileOperationFlags = fileOperationFlags;
	this->Name = std::filesystem::path(path).filename().string();
	this->Path = std::string(path);


	if (fileOperationFlags & FileOperationFlags::Read) {
		FileSize = std::filesystem::file_size(path);
		data.resize(FileSize);

		if (dataType == FileDataType::Binary) {
			this->file = new std::fstream(path, std::ios::in | std::ios::binary);
			OrionAssert(this->file->good(), "File with name: %s does not exist!", path);
			file->read((char*)data.data(), FileSize);
		}else if (dataType == FileDataType::Text) {
			this->file = new std::fstream(path, std::ios::in);
			file->read((char*)data.data(), FileSize);
		}
	}

}

void Orion::Util::File::Reload()
{
	delete this->file;
	*this = File(*this);
}
