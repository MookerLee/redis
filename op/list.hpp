#ifndef _CXXREDIS_OP_LIST_HPP_
#define _CXXREDIS_OP_LIST_HPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <string>

namespace redis {

	class client;
	class reply;

	namespace op {
		class list {
		public:
			list(client& cli);
			~list();

			/**
			* BLPOP ���б������ʽ(blocking)����ԭ�
			* ���� LPOP ����������汾���������б���û���κ�Ԫ�ؿɹ�������ʱ�����ӽ��� BLPOP ����������ֱ���ȴ���ʱ���ֿɵ���Ԫ��Ϊֹ��
			* ��������� key ����ʱ�������� key ���Ⱥ�˳�����μ������б�������һ���ǿ��б��ͷԪ�ء�
			* ��������Ϊ
			* �� BLPOP ������ʱ��������� key ��������һ���ǿ��б���ô���������ĵ�һ���ǿ��б��ͷԪ�أ����ͱ�����Ԫ���������б������һ����ɽ�����ظ������ߡ�
			* �����ڶ������ key ʱ�� BLPOP ������ key �������е��Ⱥ�˳�����μ������б�
			* ���������� job �� command �� request �����б����� job �����ڣ� command �� request �����зǿ��б������������
			* BLPOP job command request 0
			* BLPOP ��֤���ص�Ԫ������ command ����Ϊ���ǰ������� job -> ���� command -> ���� request ��������˳�򣬵�һ���ҵ��ķǿ��б�
			* ������Ϊ
			* ������и��� key �������ڻ�������б���ô BLPOP ����������ӣ�ֱ���ȴ���ʱ��������һ���ͻ��˶Ը��� key ������һ��ִ�� LPUSH �� RPUSH ����Ϊֹ��
			* ��ʱ���� timeout ����һ������Ϊ��λ��������Ϊֵ����ʱ������Ϊ 0 ��ʾ����ʱ������������ӳ�(block indefinitely) ��
			* ��ͬ��key������ͻ���ͬʱ����
			* ��ͬ�� key ���Ա�����ͻ���ͬʱ������
			* ��ͬ�Ŀͻ��˱��Ž�һ�������У������������ȷ���(first-BLPOP��first-served)��˳��Ϊ key ִ�� BLPOP ���
			* ��MULTI/EXEC�����е�BLPOP
			* BLPOP ����������ˮ��(pipline,�����ط��Ͷ������������ظ�)������������ MULTI / EXEC �鵱��û�����塣��Ϊ��Ҫ�������������������Ա�֤��ִ��ʱ��ԭ���ԣ�����Ϊ��ֹ�������ͻ���ִ�� LPUSH �� RPUSH ���
			* ��ˣ�һ���������� MULTI / EXEC ���ڵ� BLPOP �����Ϊ���ֵþ��� LPOP һ�����Կ��б��� nil ���Էǿ��б����б�Ԫ�أ��������κ�����������
			* ���ð汾��>= 2.0.0
			* ʱ�临�Ӷȣ�O(1)
			* ����ֵ��
			* ����б�Ϊ�գ�����һ�� nil ��
			* ���򣬷���һ����������Ԫ�ص��б���һ��Ԫ���Ǳ�����Ԫ�������� key ���ڶ���Ԫ���Ǳ�����Ԫ�ص�ֵ��
			* ���һ������дʱ��
			*/
			template<class... Args>
			reply blpop(Args... args);

			/**
			* BRPOP ���б������ʽ(blocking)����ԭ�
			* ���� RPOP ����������汾���������б���û���κ�Ԫ�ؿɹ�������ʱ�����ӽ��� BRPOP ����������ֱ���ȴ���ʱ���ֿɵ���Ԫ��Ϊֹ��
			* ��������� key ����ʱ�������� key ���Ⱥ�˳�����μ������б�������һ���ǿ��б��β��Ԫ�ء�
			* �������������ĸ�����Ϣ����鿴 BLPOP ��� BRPOP ���˵���Ԫ�ص�λ�ú� BLPOP ��֮ͬ�⣬��������һ�¡�
			* ���ð汾��>= 2.0.0
			* ʱ�临�Ӷȣ�O(1)
			* ����ֵ��
			* ������ָ��ʱ����û���κ�Ԫ�ر��������򷵻�һ�� nil �͵ȴ�ʱ����
			* ��֮������һ����������Ԫ�ص��б���һ��Ԫ���Ǳ�����Ԫ�������� key ���ڶ���Ԫ���Ǳ�����Ԫ�ص�ֵ��
			* ���һ������дʱ��
			*/
			template<class... Args>
			reply brpop(Args... args);

			/**
			* BRPOPLPUSH �� RPOPLPUSH �������汾���������б� source ��Ϊ��ʱ�� BRPOPLPUSH �ı��ֺ� RPOPLPUSH һ����
			* ���б� source Ϊ��ʱ�� BRPOPLPUSH ����������ӣ�ֱ���ȴ���ʱ��������һ���ͻ��˶� source ִ�� LPUSH �� RPUSH ����Ϊֹ��
			* ��ʱ���� timeout ����һ������Ϊ��λ��������Ϊֵ����ʱ������Ϊ 0 ��ʾ����ʱ������������ӳ�(block indefinitely) ��
			* ���ð汾��>= 2.2.0
			* ʱ�临�Ӷȣ�O(1)
			* ����ֵ��
			* ������ָ��ʱ����û���κ�Ԫ�ر��������򷵻�һ�� nil �͵ȴ�ʱ����
			* ��֮������һ����������Ԫ�ص��б���һ��Ԫ���Ǳ�����Ԫ�ص�ֵ���ڶ���Ԫ���ǵȴ�ʱ����
			*/
			reply brpopLpush(const std::string& source, const std::string& destination, time_t timeout = 0);

			/**
			* �����б� key �У��±�Ϊ index ��Ԫ�ء�
			* �±�(index)���� start �� stop ���� 0 Ϊ�ף�Ҳ����˵���� 0 ��ʾ�б�ĵ�һ��Ԫ�أ��� 1 ��ʾ�б�ĵڶ���Ԫ�أ��Դ����ơ�
			* ��Ҳ����ʹ�ø����±꣬�� -1 ��ʾ�б�����һ��Ԫ�أ� -2 ��ʾ�б�ĵ����ڶ���Ԫ�أ��Դ����ơ�
			* ��� key �����б����ͣ�����һ������
			* ���ð汾��>= 1.0.0
			* ʱ�临�Ӷȣ�
			* O(N)�� N Ϊ�����±� index �����о�����Ԫ��������
			* ��ˣ����б��ͷԪ�غ�βԪ��ִ�� LINDEX ������Ӷ�ΪO(1)��
			* ����ֵ:
			* �б����±�Ϊ index ��Ԫ�ء�
			* ��� index ������ֵ�����б�����䷶Χ��(out of range)������ nil ��
			*/
			std::string index(const std::string& key, size_t idx);

			/**
			* ��ֵ value ���뵽�б� key ���У�λ��ֵ pivot ֮ǰ��֮��
			* �� pivot ���������б� key ʱ����ִ���κβ�����
			* �� key ������ʱ�� key ����Ϊ���б���ִ���κβ�����
			* ��� key �����б����ͣ�����һ������
			* ���ð汾��>= 2.2.0
			* ʱ�临�Ӷ�:
			* O(N)�� N ΪѰ�� pivot �����о�����Ԫ��������
			* ����ֵ:
			* �������ִ�гɹ������ز���������֮���б�ĳ��ȡ�
			* ���û���ҵ� pivot ������ -1 ��
			* ��� key �����ڻ�Ϊ���б����� 0 ��
			*/
			long long insertBefore(const std::string& key, const std::string& pivot, const std::string& value);
			long long insertAfter(const std::string& key, const std::string& pivot, const std::string& value);

			/**
			* �����б� key �ĳ��ȡ�
			* ��� key �����ڣ��� key ������Ϊһ�����б����� 0 .
			* ��� key �����б����ͣ�����һ������
			* ���ð汾��>= 1.0.0
			* ʱ�临�Ӷȣ�O(1)
			* ����ֵ���б� key �ĳ��ȡ�
			*/
			long long len(const std::string& key);

			/**
			* �Ƴ��������б� key ��ͷԪ�ء�
			* ���ð汾��>= 1.0.0
			* ʱ�临�Ӷȣ�O(1)
			* ����ֵ��
			* �б��ͷԪ�ء�
			* �� key ������ʱ������ nil ��
			*/
			std::string pop(const std::string& key);

			/**
			* ��һ������ֵ value ���뵽�б� key �ı�ͷ
			* ����ж�� value ֵ����ô���� value ֵ�������ҵ�˳�����β��뵽��ͷ�� 
			* ����˵���Կ��б� mylist ִ������ LPUSH mylist a b c ���б��ֵ���� c b a ��
			* ���ͬ��ԭ���Ե�ִ�� LPUSH mylist a �� LPUSH mylist b �� LPUSH mylist c �������
			* ��� key �����ڣ�һ�����б�ᱻ������ִ�� LPUSH ������
			* �� key ���ڵ������б�����ʱ������һ������
			* ���ð汾��>= 1.0.0
			* ʱ�临�Ӷȣ�O(1)
			* ����ֵ��
			* ִ�� LPUSH ������б�ĳ��ȡ�
			*/
			template<class... Args>
			long long push(const std::string& key, Args... values);

			/*
			* ��ֵ value ���뵽�б� key �ı�ͷ�����ҽ��� key ���ڲ�����һ���б�
			* �� LPUSH �����෴���� key ������ʱ�� LPUSHX ����ʲôҲ������
			* ���ð汾��>= 2.2.0
			* ʱ�临�Ӷȣ�O(1)
			* ����ֵ��
			* LPUSHX ����ִ��֮�󣬱�ĳ��ȡ�
			*/
			template<class... Args>
			long long pushX(const std::string& key, Args... values);

			/**
			* �����б� key ��ָ�������ڵ�Ԫ�أ�������ƫ���� start �� stop ָ����
			* �±�(index)���� start �� stop ���� 0 Ϊ�ף�Ҳ����˵���� 0 ��ʾ�б�ĵ�һ��Ԫ�أ��� 1 ��ʾ�б�ĵڶ���Ԫ�أ��Դ����ơ�
			* ��Ҳ����ʹ�ø����±꣬�� -1 ��ʾ�б�����һ��Ԫ�أ� -2 ��ʾ�б�ĵ����ڶ���Ԫ�أ��Դ����ơ�
			* ע��LRANGE����ͱ���������亯��������
			* ��������һ������һ�ٸ�Ԫ�ص��б��Ը��б�ִ�� LRANGE list 0 10 ��
			* �����һ������11��Ԫ�ص��б������ stop �±�Ҳ�� LRANGE �����ȡֵ��Χ֮��(������)��
			* ���ĳЩ���Ե����亯�����ܲ�һ�£�����Ruby�� Range.new �� Array#slice ��Python�� range() ������
			* ������Χ���±�
			* ������Χ���±�ֵ�����������
			* ��� start �±���б������±� end ( LLEN list ��ȥ 1 )��Ҫ����ô LRANGE ����һ�����б�
			* ��� stop �±�� end �±껹Ҫ��Redis�� stop ��ֵ����Ϊ end ��
			* ���ð汾��>= 1.0.0
			* ʱ�临�Ӷ�:
			* O(S+N)�� S Ϊƫ���� start �� N Ϊָ��������Ԫ�ص�������
			* ����ֵ:
			* һ���б�����ָ�������ڵ�Ԫ�ء�
			*/
			reply range(const std::string& key, size_t start = 0, size_t stop = -1);

			/**
			* ���ݲ��� count ��ֵ���Ƴ��б�������� value ��ȵ�Ԫ�ء�
			* count ��ֵ���������¼��֣�
			* count > 0 : �ӱ�ͷ��ʼ���β�������Ƴ��� value ��ȵ�Ԫ�أ�����Ϊ count ��
			* count < 0 : �ӱ�β��ʼ���ͷ�������Ƴ��� value ��ȵ�Ԫ�أ�����Ϊ count �ľ���ֵ��
			* count = 0 : �Ƴ����������� value ��ȵ�ֵ��
			* ���ð汾��>= 1.0.0
			* ʱ�临�Ӷȣ�
			* O(N)�� N Ϊ�б�ĳ��ȡ�
			* ����ֵ��
			* ���Ƴ�Ԫ�ص�������
			* ��Ϊ�����ڵ� key �������ձ�(empty list)�����Ե� key ������ʱ�� LREM �������Ƿ��� 0 ��
			*/
			long long remove(const std::string& key, size_t count, const std::string& value);

			/*
			* ���б� key �±�Ϊ index ��Ԫ�ص�ֵ����Ϊ value ��
			* �� index ����������Χ�����һ�����б�( key ������)���� LSET ʱ������һ������
			* ���ð汾��>= 1.0.0
			* ʱ�临�Ӷȣ�
			* ��ͷԪ�ػ�βԪ�ؽ��� LSET ���������Ӷ�Ϊ O(1)��
			* ��������£�Ϊ O(N)�� N Ϊ�б�ĳ��ȡ�
			* ����ֵ��
			* �����ɹ����� ok �����򷵻ش�����Ϣ��
			*/
			void set(const std::string& key, size_t index, const std::string& value);

			/*
			* ��һ���б�����޼�(trim)������˵�����б�ֻ����ָ�������ڵ�Ԫ�أ�����ָ������֮�ڵ�Ԫ�ض�����ɾ����
			* �ٸ����ӣ�ִ������ LTRIM list 0 2 ����ʾֻ�����б� list ��ǰ����Ԫ�أ�����Ԫ��ȫ��ɾ����
			* �±�(index)���� start �� stop ���� 0 Ϊ�ף�Ҳ����˵���� 0 ��ʾ�б�ĵ�һ��Ԫ�أ��� 1 ��ʾ�б�ĵڶ���Ԫ�أ��Դ����ơ�
			* ��Ҳ����ʹ�ø����±꣬�� -1 ��ʾ�б�����һ��Ԫ�أ� -2 ��ʾ�б�ĵ����ڶ���Ԫ�أ��Դ����ơ�
			* �� key �����б�����ʱ������һ������
			* LTRIM ����ͨ���� LPUSH ����� RPUSH �������ʹ�ã��ٸ����ӣ�
			* LPUSH log newest_log
			* LTRIM log 0 99
			* �������ģ����һ����־����ÿ�ν�������־ newest_log �ŵ� log �б��У�
			* ����ֻ�������µ� 100 �ע�⵱����ʹ�� LTRIM ����ʱ��ʱ�临�Ӷ���O(1)����Ϊƽ������£�ÿ��ֻ��һ��Ԫ�ر��Ƴ���
			* ע��LTRIM����ͱ���������亯��������
			* ��������һ������һ�ٸ�Ԫ�ص��б� list ���Ը��б�ִ�� LTRIM list 0 10 ��
			* �����һ������11��Ԫ�ص��б������ stop �±�Ҳ�� LTRIM �����ȡֵ��Χ֮��(������)��
			* ���ĳЩ���Ե����亯�����ܲ�һ�£�����Ruby�� Range.new �� Array#slice ��Python�� range() ������
			* ������Χ���±�
			* ������Χ���±�ֵ�����������
			* ��� start �±���б������±� end ( LLEN list ��ȥ 1 )��Ҫ�󣬻��� start > stop �� 
			* LTRIM ����һ�����б�(��Ϊ LTRIM �Ѿ��������б����)��
			* ��� stop �±�� end �±껹Ҫ��Redis�� stop ��ֵ����Ϊ end ��
			*
			* ���ð汾��>= 1.0.0
			* ʱ�临�Ӷ�:
			* O(N)�� N Ϊ���Ƴ���Ԫ�ص�������
			* ����ֵ:
			* ����ִ�гɹ�ʱ������ ok ��
			*/
			void trim(const std::string& key, size_t start = 0, size_t stop = -1);

			/*
			* �Ƴ��������б� key ��βԪ�ء�
			* ���ð汾��>= 1.0.0
			* ʱ�临�Ӷȣ�O(1)
			* ����ֵ��
			* �б��βԪ�ء�
			* �� key ������ʱ������ nil ��
			*/
			std::string rpop(const std::string& key);

			/*
			* ���� RPOPLPUSH ��һ��ԭ��ʱ���ڣ�ִ����������������
			* ���б� source �е����һ��Ԫ��(βԪ��)�����������ظ��ͻ��ˡ�
			* �� source ������Ԫ�ز��뵽�б� destination ����Ϊ destination �б�ĵ�ͷԪ�ء�
			* �ٸ����ӣ����������б� source �� destination �� 
			* source �б���Ԫ�� a, b, c �� destination �б���Ԫ�� x, y, z ��
			* ִ�� RPOPLPUSH source destination ֮�� source �б����Ԫ�� a, b �� 
			* destination �б����Ԫ�� c, x, y, z ������Ԫ�� c �ᱻ���ظ��ͻ��ˡ�
			* ��� source �����ڣ�ֵ nil �����أ����Ҳ�ִ������������
			* ��� source �� destination ��ͬ�����б��еı�βԪ�ر��ƶ�����ͷ�������ظ�Ԫ�أ����԰�����������������б����ת(rotation)������
			* ���ð汾��>= 1.2.0
			* ʱ�临�Ӷȣ�O(1)
			* ����ֵ����������Ԫ�ء�
			*/
			std::string rpopLpush(const std::string& source, const std::string& destination);

			/*
			* ��һ������ֵ value ���뵽�б� key �ı�β(���ұ�)��
			* ����ж�� value ֵ����ô���� value ֵ�������ҵ�˳�����β��뵽��β�������һ�����б� mylist ִ�� RPUSH mylist a b c ���ó��Ľ���б�Ϊ a b c ����ͬ��ִ������ RPUSH mylist a �� RPUSH mylist b �� RPUSH mylist c ��
			* ��� key �����ڣ�һ�����б�ᱻ������ִ�� RPUSH ������
			* �� key ���ڵ������б�����ʱ������һ������
			* ���ð汾��>= 1.0.0
			* ʱ�临�Ӷȣ�O(1)
			* ����ֵ��ִ�� RPUSH �����󣬱�ĳ��ȡ�
			*/
			template<class... Args>
			long long rpush(const std::string& key, Args... values);

			/*
			* ��ֵ value ���뵽�б� key �ı�β�����ҽ��� key ���ڲ�����һ���б�
			* �� RPUSH �����෴���� key ������ʱ�� RPUSHX ����ʲôҲ������
			* ���ð汾��>= 2.2.0
			* ʱ�临�Ӷȣ�O(1)
			* ����ֵ��RPUSHX ����ִ��֮�󣬱�ĳ��ȡ�
			*/
			long long rpushX(const std::string& key, const std::string& value);
		private:
			client& cli_;
		};
	};
};

#if !defined(CORE_ONLY_HEADER)
#include "impl/list.hpp"
#endif

#endif
