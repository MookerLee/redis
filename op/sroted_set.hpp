
#ifndef _CXXREDIS_OP_SORTED_SET_HPP_
#define _CXXREDIS_OP_SORTED_SET_HPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

namespace redis {

	class client;
	class reply;

	namespace op {
		class srotedSet {
		public:
			srotedSet(client& cli);
			~srotedSet();

			/**
			* 将一个或多个 member 元素及其 score 值加入到有序集 key 当中。
			* 如果某个 member 已经是有序集的成员，那么更新这个 member 的 score 值，并通过重新插入这个 member 元素，来保证该 member 在正确的位置上。
			* score 值可以是整数值或双精度浮点数。
			* 如果 key 不存在，则创建一个空的有序集并执行 ZADD 操作。
			* 当 key 存在但不是有序集类型时，返回一个错误。
			* 对有序集的更多介绍请参见 sorted set 。
			* 可用版本：>= 1.2.0
			* 时间复杂度:O(M*log(N))， N 是有序集的基数， M 为成功添加的新成员的数量。
			* 返回值:被成功添加的新成员的数量，不包括那些被更新的、已经存在的成员。
			*/
			template<class... Args>
			long long add(const std::string& key, std::initializer_list<Args>... scoreMembers);

		private:
			client& cli_;
		};
	};
};

#if !defined(CORE_ONLY_HEADER)
#include "impl/sroted_set.hpp"
#endif

#endif