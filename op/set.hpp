#ifndef _CXXREDIS_OP_SET_HPP_
#define _CXXREDIS_OP_SET_HPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)
namespace redis {

	class client;
	class reply;

	namespace op {

		class set {

		public:
			set(client& cli);
			~set();

			/**
			* 将一个或多个 member 元素加入到集合 key 当中，已经存在于集合的 member 元素将被忽略。
			* 假如 key 不存在，则创建一个只包含 member 元素作成员的集合。
			* 当 key 不是集合类型时，返回一个错误。
			* 可用版本：>= 1.0.0
			* 时间复杂度:O(N)， N 是被添加的元素的数量。
			* 返回值:
			* 被添加到集合中的新元素的数量，不包括被忽略的元素。
			*/
			template<class... Args>
			long long add(const std::string& key, Args... members);

		private:
			client& cli_;
		};
	}
};
#if !defined(CORE_ONLY_HEADER)
#include "impl/set.hpp"
#endif

#endif