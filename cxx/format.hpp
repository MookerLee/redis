#pragma once
#include <string>
#include <vector>

namespace CXXRedis {

	class format {

	public:
		template<class... Args>
		static std::string formatCmd(const std::string& cmd, Args... args)
		{		
			analysisArgs(args...);	
			std::string formatStr(cmd);
			
			for (auto argStr : argStrings_) 
			{
				formatStr.append(" ");
				formatStr.append(argStr);
			}

			argStrings_.clear();
			return formatStr;
		}

	private:
		template<class... Args>
		static void analysisArgs(const std::string& arg,Args... args)
		{
			argStrings_.push_back(arg);
			analysisArgs(args...);
		}
		static void analysisArgs()
		{
			
		}

		static std::vector<std::string> argStrings_;

	};
};