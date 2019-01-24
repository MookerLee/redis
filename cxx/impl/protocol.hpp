#include <string>
#include <list>
#include <algorithm>

namespace CXXRedis {

	class protocol {
		
	public:
		static std::string serialize(const std::string& simpleCmd)
		{
			std::list<std::string> output;
			splitCmd(output, simpleCmd);

			return "";
		}

		static void splitCmd(std::list<std::string>& output, const std::string& input)
		{
			if (input.empty()) return;

			if(input[0] == ' ') return splitCmd(output, input.substr(1));

			size_t pos = std::string::npos;

			const char find = input[0] == '\"' ? '\"' : ' ';
			if ((pos = input.find_first_of(find,1)) == std::string::npos)
			{
				output.push_back(input);
				return;
			}

			output.push_back(input.substr(0,pos + 1));

			return splitCmd(output, input.substr(pos + 1));

		}
	};
};