
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
			* ��һ������ member Ԫ�ؼ��� score ֵ���뵽���� key ���С�
			* ���ĳ�� member �Ѿ������򼯵ĳ�Ա����ô������� member �� score ֵ����ͨ�����²������ member Ԫ�أ�����֤�� member ����ȷ��λ���ϡ�
			* score ֵ����������ֵ��˫���ȸ�������
			* ��� key �����ڣ��򴴽�һ���յ����򼯲�ִ�� ZADD ������
			* �� key ���ڵ�������������ʱ������һ������
			* �����򼯵ĸ��������μ� sorted set ��
			* ���ð汾��>= 1.2.0
			* ʱ�临�Ӷ�:O(M*log(N))�� N �����򼯵Ļ����� M Ϊ�ɹ���ӵ��³�Ա��������
			* ����ֵ:���ɹ���ӵ��³�Ա����������������Щ�����µġ��Ѿ����ڵĳ�Ա��
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