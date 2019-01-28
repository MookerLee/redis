#include <string>
namespace redis{

	class stringConvert {
	public:
		static std::string toString(const char* val)
		{
			return std::string(val);
		}
		static std::string toString(int val)
		{
			return std::to_string(val);
		}
		static std::string toString(unsigned int val)
		{
			return std::to_string(val);
		}
		static std::string toString(long long val)
		{
			return std::to_string(val);
		}
		static std::string toString(float val)
		{
			return std::to_string(val);
		}
		static std::string toString(double val)
		{
			return std::to_string(val);
		}
		static std::string toString(const std::string& val)
		{
			return val;
		}
	};
}