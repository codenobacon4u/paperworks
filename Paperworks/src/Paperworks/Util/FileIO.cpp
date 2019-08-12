#include "pwpch.h"
#include "FileIO.h"

namespace Paperworks {

	std::string FileIO::ReadFile(const std::string& path)
	{
		PW_CORE_INFO("Opening file {0}", path);
		std::ifstream file(path);

		if (!file.is_open()) {
			PW_CORE_ERROR("Failed to find file at '{0}'", path);
		}
		std::stringstream stream;

		stream << file.rdbuf();

		file.close();
		
		return stream.str();
	}
}