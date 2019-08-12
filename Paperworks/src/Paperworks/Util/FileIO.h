#pragma once
#include <fstream>

namespace Paperworks {
	class FileIO {
	public:
		static std::string ReadFile(const std::string& path);
	};
}