#pragma once

#include <string>

namespace Skylicht
{
	class CMD5
	{
	public:
		static std::string calc(const char* file);

		static std::string calc(unsigned char* buffer, int size);
	};

}