#ifndef _CXXREDIS_OP_SET_HPP_
#define _CXXREDIS_OP_SET_HPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <string>

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

			/*
			* ���ؼ��� key �Ļ���(������Ԫ�ص�����)��
			* ���ð汾��>= 1.0.0
			* ʱ�临�Ӷ�:O(1)
			* ����ֵ��
			* ���ϵĻ�����
			* �� key ������ʱ������ 0 ��
			*/
			long long card(const std::string& key);

			/*
			* ����һ�����ϵ�ȫ����Ա���ü��������и�������֮��Ĳ��
			* �����ڵ� key ����Ϊ�ռ���
			* ���ð汾��>= 1.0.0
			* ʱ�临�Ӷ�:O(N)�� N �����и������ϵĳ�Ա����֮�͡�
			* ����ֵ: һ���������Ա���б�
			*/
			template<class... Args>
			reply diff(Args... keys);

			/*
			* �����������ú� SDIFF ���ƣ�������������浽 destination ���ϣ������Ǽ򵥵ط��ؽ������
			* ��� destination �����Ѿ����ڣ����串�ǡ�
			* destination ������ key ����
			* ���ð汾��>= 1.0.0
			* ʱ�临�Ӷ�:O(N)�� N �����и������ϵĳ�Ա����֮�͡�
			* ����ֵ:������е�Ԫ��������
			*/
			template<class... Args>
			long long diffStore(const std::string& destination, Args... keys);

			/*
			* ����һ�����ϵ�ȫ����Ա���ü��������и������ϵĽ�����
			* �����ڵ� key ����Ϊ�ռ���
			* ���������ϵ�����һ���ռ�ʱ�����ҲΪ�ռ�(���ݼ������㶨��)��
			* ���ð汾��>= 1.0.0
			* ʱ�临�Ӷ�: O(N * M)�� N Ϊ�������ϵ��л�����С�ļ��ϣ� M Ϊ�������ϵĸ�����
			* ����ֵ: ������Ա���б�
			*/
			template<class... Args>
			reply inter(Args... keys);

			/*
			* ������������� SINTER ���������������浽 destination ���ϣ������Ǽ򵥵ط��ؽ������
			* ��� destination �����Ѿ����ڣ����串�ǡ�
			* destination ������ key ����
			* ���ð汾��>= 1.0.0
			* ʱ�临�Ӷ�:O(N * M)�� N Ϊ�������ϵ��л�����С�ļ��ϣ� M Ϊ�������ϵĸ�����
			* ����ֵ:������еĳ�Ա������
			*/
			template<class... Args>
			long long interStore(const std::string& destination, Args... keys);

			/*
			* �ж� member Ԫ���Ƿ񼯺� key �ĳ�Ա��
			* ���ð汾��>= 1.0.0
			* ʱ�临�Ӷ�:O(1)
			* ����ֵ:
			* ��� member Ԫ���Ǽ��ϵĳ�Ա������ 1 ��
			* ��� member Ԫ�ز��Ǽ��ϵĳ�Ա���� key �����ڣ����� 0 ��
			*/
			bool isMember(const std::string& key, const std::string& member);

			/*
			* ���ؼ��� key �е����г�Ա��
			* �����ڵ� key ����Ϊ�ռ��ϡ�
			* ���ð汾��>= 1.0.0
			* ʱ�临�Ӷ�:O(N)�� N Ϊ���ϵĻ�����
			* ����ֵ:�����е����г�Ա��
			*/
			reply members(const std::string& key);

			/*
			* �� member Ԫ�ش� source �����ƶ��� destination ���ϡ�
			* SMOVE ��ԭ���Բ�����
			* ��� source ���ϲ����ڻ򲻰���ָ���� member Ԫ�أ��� SMOVE ���ִ���κβ����������� 0 ��
			* ���� member Ԫ�ش� source �����б��Ƴ�������ӵ� destination ������ȥ��
			* �� destination �����Ѿ����� member Ԫ��ʱ�� SMOVE ����ֻ�Ǽ򵥵ؽ� source �����е� member Ԫ��ɾ����
			* �� source �� destination ���Ǽ�������ʱ������һ������
			* ���ð汾��>= 1.0.0
			* ʱ�临�Ӷ�:O(1)
			* ����ֵ:
			* ��� member Ԫ�ر��ɹ��Ƴ������� 1 ��
			* ��� member Ԫ�ز��� source ���ϵĳ�Ա������û���κβ����� destination ����ִ�У���ô���� 0 ��
			*/
			bool move(const std::string& source, const std::string& destination, const std::string& member);

			/*
			* �Ƴ������ؼ����е�һ�����Ԫ�ء�
			* ���ֻ���ȡһ�����Ԫ�أ��������Ԫ�شӼ����б��Ƴ��Ļ�������ʹ�� SRANDMEMBER ���
			* ���ð汾��>= 1.0.0
			* ʱ�临�Ӷ�:O(1)
			* ����ֵ:
			* ���Ƴ������Ԫ�ء�
			* �� key �����ڻ� key �ǿռ�ʱ������ nil ��
			*/
			std::string pop(const std::string& key);

			/*
			* �������ִ��ʱ��ֻ�ṩ�� key ��������ô���ؼ����е�һ�����Ԫ�ء�
			* �� Redis 2.6 �汾��ʼ�� SRANDMEMBER ������ܿ�ѡ�� count ������
			* ��� count Ϊ��������С�ڼ��ϻ�������ô�����һ������ count ��Ԫ�ص����飬�����е�Ԫ�ظ�����ͬ����� count ���ڵ��ڼ��ϻ�������ô�����������ϡ�
			* ��� count Ϊ��������ô�����һ�����飬�����е�Ԫ�ؿ��ܻ��ظ����ֶ�Σ�������ĳ���Ϊ count �ľ���ֵ��
			* �ò����� SPOP ���ƣ��� SPOP �����Ԫ�شӼ������Ƴ������أ��� SRANDMEMBER ������������Ԫ�أ������Լ��Ͻ����κθĶ���
			*
			* ���ð汾��>= 1.0.0
			* ʱ�临�Ӷ�:
			* ֻ�ṩ key ����ʱΪ O(1) ��
			* ����ṩ�� count ��������ôΪ O(N) ��N Ϊ���������Ԫ�ظ�����
			* ����ֵ:
			* ֻ�ṩ key ����ʱ������һ��Ԫ�أ��������Ϊ�գ����� nil ��
			* ����ṩ�� count ��������ô����һ�����飻�������Ϊ�գ����ؿ����顣
			*/
			reply randMember(const std::string& key,size_t count = 0xffffffffffffffff);

			/*
			* �Ƴ����� key �е�һ������ member Ԫ�أ������ڵ� member Ԫ�ػᱻ���ԡ�
			* �� key ���Ǽ������ͣ�����һ������
			* ���ð汾��>= 1.0.0
			* ʱ�临�Ӷ�:O(N)�� N Ϊ���� member Ԫ�ص�������
			* ����ֵ:���ɹ��Ƴ���Ԫ�ص������������������Ե�Ԫ�ء�
			*/
			template<class... Args>
			long long remove(const std::string& key, Args... members);

			/*
			* ����һ�����ϵ�ȫ����Ա���ü��������и������ϵĲ�����
			* �����ڵ� key ����Ϊ�ռ���
			* ���ð汾��>= 1.0.0
			* ʱ�临�Ӷ�:O(N)�� N �����и������ϵĳ�Ա����֮�͡�
			* ����ֵ:������Ա���б�
			*/
			template<class... Args>
			reply sunion(Args... keys);

			/*
			* ������������� SUNION ���������������浽 destination ���ϣ������Ǽ򵥵ط��ؽ������
			* ��� destination �Ѿ����ڣ����串�ǡ�
			* destination ������ key ����
			* ���ð汾��>= 1.0.0
			* ʱ�临�Ӷ�:O(N)�� N �����и������ϵĳ�Ա����֮�͡�
			* ����ֵ:������е�Ԫ��������
			*/
			template<class... Args>
			reply sunionStore(const std::string& destination, Args... keys);

			/**
			*
			* ���ڵ�����ǰ���ݿ��е����ݿ����
			*/
			reply scan(const std::string& key, int cursor = 0, const std::string& matchPattern = "*", int count = 10);
		private:
			client& cli_;
		};
	};
};

#if !defined(CORE_ONLY_HEADER)
#include "impl/set.hpp"
#endif

#endif