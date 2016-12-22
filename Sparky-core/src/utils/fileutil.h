#pragma once
#include <fstream>

namespace sparky {

	class FileUtils {
	public:
		static std::string read_file(const char* filepath);
	};

}
