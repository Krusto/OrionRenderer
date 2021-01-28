#pragma once
#include <string>
#include <vector>
#include <any>
#include "Array.h"
namespace Orion {
	namespace Util {
		enum class FileDataType {
			None,
			Binary,
			Text
		};
		enum FileOperationFlags {
			None = 0,
			Read = 1,
			Write = 2,
			CreateIfNotExist = 4,
		};
		class File {
		public:
			File() = default;
			File(const File&) = default;
			File& operator=(const File&) = default;
			~File() { 
			}

			File(const char* path,FileDataType dataType,FileOperationFlags fileOperationFlags);
			void Reload();

			operator std::fstream&() { return *file; }

			void Open(const char* path, FileDataType dataType, FileOperationFlags fileOperationFlags) 
			{
				*this = File(path, dataType, fileOperationFlags);
			}
			void Free() {
				this->~File();
			}
			std::string Name = "";
			std::string Path = "";
			std::vector<uint8_t> data;

			std::fstream* file;
			uint64_t FileSize = 0;
			FileDataType dataType = FileDataType::None;
			FileOperationFlags fileOperationFlags = FileOperationFlags::None;
		};
	}
}