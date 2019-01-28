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
			* ��һ������ member Ԫ�ؼ��뵽���� key ���У��Ѿ������ڼ��ϵ� member Ԫ�ؽ������ԡ�
			* ���� key �����ڣ��򴴽�һ��ֻ���� member Ԫ������Ա�ļ��ϡ�
			* �� key ���Ǽ�������ʱ������һ������
			* ���ð汾��>= 1.0.0
			* ʱ�临�Ӷ�:O(N)�� N �Ǳ���ӵ�Ԫ�ص�������
			* ����ֵ:
			* ����ӵ������е���Ԫ�ص������������������Ե�Ԫ�ء�
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