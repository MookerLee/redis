
namespace redis {


	class protocol::sender {

	public:
		static std::string serializeSimpleCommand(const std::string& simpleCmd)
		{
			std::list<std::string> commands;
			splitString(commands, simpleCmd, " ");
			return serializeListCommand(commands);
		}

		template<class... Args>
		static std::string serializeSafeCommand(const std::string& cmd, Args... args)
		{
			std::list<std::string> commands{ cmd };
			analysisArgs(commands, std::forward<Args>(args)...);
			return serializeListCommand(commands);

		}
		template<class ValueType, class... Args>
		static void analysisArgs(std::list<std::string>& commands, ValueType arg, Args... args)
		{
			commands.push_back(stringConvert::toString(arg));
			analysisArgs(commands, args...);
		}
		static void analysisArgs(std::list<std::string>&) {}

		static std::string serializeListCommand(const std::list<std::string>& commands)
		{
			/************************************************************************/
			/*      *<参数数量> CR LF                                                */
			/*		$<参数 1 的字节数量> CR LF										*/
			/*		...																*/
			/*		$<参数 N 的字节数量> CR LF										*/
			/*		<参数 N 的数据> CR LF												*/
			/************************************************************************/
			std::string serializeStr;

			serializeStr.append("*");
			serializeStr.append(std::to_string(commands.size()));
			serializeStr.append("\r\n");

			for (const auto& command : commands)
			{
				serializeStr.append("$");
				serializeStr.append(std::to_string(command.size()));
				serializeStr.append("\r\n");
				serializeStr.append(command.c_str(), command.size());
				serializeStr.append("\r\n");
			}

			return serializeStr;
		}

		static void splitString(std::list<std::string>& commands, const std::string& simpleCmd, const std::string& split)
		{
			if (simpleCmd.empty()) return;

			if (simpleCmd[0] == ' ') return splitString(commands, simpleCmd.substr(1), split);

			size_t pos = std::string::npos;

			std::string _spit = split;
			if (simpleCmd[0] == '\"') _spit = '\"';

			if ((pos = simpleCmd.find_first_of(_spit, 1)) == std::string::npos)
			{
				commands.push_back(simpleCmd);
				return;
			}

			commands.push_back(simpleCmd.substr(0, pos));

			return splitString(commands, simpleCmd.substr(pos + _spit.size()), split);
		}
	};
};