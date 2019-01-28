namespace redis {
	namespace op {
		list::list(client& cli)
			:cli_(cli)
		{

		}
		list::~list()
		{
			
		}
		template<class... Args>
		reply list::blpop(Args... args)
		{
			return cli_.sendSafeCommand("BLPOP", args...);
		}
		template<class... Args>
		reply list::brpop(Args... args)
		{
			return cli_.sendSafeCommand("BRPOP", args...);
		}

		reply list::brpopLpush(const std::string& source, const std::string& destination, time_t timeout)
		{
			return cli_.sendSafeCommand("BRPOPLPUSH", source, destination, timeout);
		}
		std::string list::index(const std::string& key, size_t idx)
		{
			return cli_.sendSafeCommand("LINDEX", key, idx).asString();
		}
		long long list::insertBefore(const std::string& key, const std::string& pivot, const std::string& value)
		{
			return cli_.sendSafeCommand("LINSERT", key, "BEFORE", pivot, value).asInteger();
		}
		long long list::insertAfter(const std::string& key, const std::string& pivot, const std::string& value)
		{
			return cli_.sendSafeCommand("LINSERT", key, "AFTER", pivot, value).asInteger();
		}
		long long list::len(const std::string& key)
		{
			return cli_.sendSafeCommand("LLEN", key).asInteger();
		}
		std::string list::pop(const std::string& key)
		{
			return cli_.sendSafeCommand("LPOP", key).asString();
		}
		template<class... Args>
		long long list::push(const std::string& key, Args... values)
		{
			return cli_.sendSafeCommand("LPUSH", key,values...).asInteger();
		}
		template<class... Args>
		long long list::pushX(const std::string& key, Args... values)
		{
			return cli_.sendSafeCommand("LPUSHX", key, values...).asInteger();
		}
		reply list::range(const std::string& key, size_t start /* = 0 */, size_t stop /* = -1 */)
		{
			return cli_.sendSafeCommand("LRANGE", key, start,stop);
		}
		long long list::remove(const std::string& key, size_t count, const std::string& value)
		{
			return cli_.sendSafeCommand("LREM", key, count, value).asInteger();
		}
		void list::set(const std::string& key, size_t index, const std::string& value)
		{
			cli_.sendSafeCommand("LSET", key, index, value);
		}
		void list::trim(const std::string& key, size_t start /* = 0 */, size_t stop /* = -1 */)
		{
			cli_.sendSafeCommand("LTRIM", key, start, stop);
		}
		std::string list::rpop(const std::string& key)
		{
			return cli_.sendSafeCommand("RPOP", key).asString();
		}
		std::string list::rpopLpush(const std::string& source, const std::string& destination)
		{
			return cli_.sendSafeCommand("RPOPLPUSH", source, destination).asString();
		}
		template<class... Args>
		long long list::rpush(const std::string& key, Args... values)
		{
			return cli_.sendSafeCommand("RPUSH", key, values...).asInteger();
		}
		long long list::rpushX(const std::string& key, const std::string& value)
		{
			return cli_.sendSafeCommand("RPUSHX", key, value).asInteger();
		}
	}
};