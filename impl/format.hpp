#pragma once

#ifndef CXXREDIS_FORMAT_HPP_
#define CXXREDIS_FORMAT_HPP_

#include <string>
#include <vector>

namespace redis {

	class format {

	public:
		

		template<class... Args>
		static std::string formatPairs(const std::string& cmd, std::initializer_list<Args>... pairs)
		{
			formatString_.assign(cmd);
			analysisPairs(pairs...);
			return formatString_;
		}


		template <class ValueType, class... Args>
		static void analysisPairs(ValueType pair, std::initializer_list<Args>... pairs)
		{
			for (auto it = pair.begin(); it != pair.end(); ++it)
			{
				formatString_ += " ";
				formatString_ += *it;
			}
			analysisPairs(pairs...);
		}
		static void analysisPairs() {}
			
		

		static std::string formatString_;

	};
	std::string format::formatString_;

};

#endif