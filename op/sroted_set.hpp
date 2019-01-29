

#ifndef _CXXREDIS_OP_SORTED_SET_HPP_
#define _CXXREDIS_OP_SORTED_SET_HPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <map>
#include <list>

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
			long long zadd(const std::string& key, const std::multimap<long long,std::string>& scoreMembers);

			/**
			* �������� key �Ļ�����
			* ���ð汾��>= 1.2.0
			* ʱ�临�Ӷ�:O(1)
			* ����ֵ:
			* �� key ����������������ʱ���������򼯵Ļ�����
			* �� key ������ʱ������ 0 ��
			*/
			long long zcard(const std::string& key);

			/**
			* �������� key �У� score ֵ�� min �� max ֮��(Ĭ�ϰ��� score ֵ���� min �� max )�ĳ�Ա��������
			* ���ð汾��>= 2.0.0
			* ʱ�临�Ӷ�:O(log(N))�� N Ϊ���򼯵Ļ�����
			* ����ֵ:score ֵ�� min �� max ֮��ĳ�Ա��������
			*/
			long long zcount(const std::string& key, const std::string& min = "-inf", const std::string& max = "+inf");

			/**
			* Ϊ���� key �ĳ�Ա member �� score ֵ�������� increment ��
			* ����ͨ������һ������ֵ increment ���� score ��ȥ��Ӧ��ֵ������ ZINCRBY key -5 member �������� member �� score ֵ��ȥ 5 ��
			* �� key �����ڣ��� member ���� key �ĳ�Աʱ�� ZINCRBY key increment member ��ͬ�� ZADD key increment member ��
			* �� key ������������ʱ������һ������
			* score ֵ����������ֵ��˫���ȸ�������
			* ���ð汾��>= 1.2.0
			* ʱ�临�Ӷ�:O(log(N))
			* ����ֵ:member ��Ա���� score ֵ�����ַ�����ʽ��ʾ��
			*/
			std::string zincrby(const std::string& key, const std::string& increment, const std::string& member);

			/**
			* �������� key �У�ָ�������ڵĳ�Ա��
			* ���г�Ա��λ�ð� score ֵ����(��С����)������
			* ������ͬ score ֵ�ĳ�Ա���ֵ���(lexicographical order )�����С�
			* �������Ҫ��Ա�� score ֵ�ݼ�(�Ӵ�С)�����У���ʹ�� ZREVRANGE ���
			* �±���� start �� stop ���� 0 Ϊ�ף�Ҳ����˵���� 0 ��ʾ���򼯵�һ����Ա���� 1 ��ʾ���򼯵ڶ�����Ա���Դ����ơ�
			* ��Ҳ����ʹ�ø����±꣬�� -1 ��ʾ���һ����Ա�� -2 ��ʾ�����ڶ�����Ա���Դ����ơ�
			* ������Χ���±겢�����������
			* ����˵���� start ��ֵ�����򼯵�����±껹Ҫ�󣬻��� start > stop ʱ�� ZRANGE ����ֻ�Ǽ򵥵ط���һ�����б�
			* ��һ���棬���� stop ������ֵ�����򼯵�����±껹Ҫ����ô Redis �� stop ��������±�������
			* ����ͨ��ʹ�� WITHSCORES ѡ����ó�Ա������ score ֵһ�����أ������б��� value1,score1, ..., valueN,scoreN �ĸ�ʽ��ʾ��
			* �ͻ��˿���ܻ᷵��һЩ�����ӵ��������ͣ��������顢Ԫ��ȡ�
			* ���ð汾��>= 1.2.0
			* ʱ�临�Ӷ�:O(log(N)+M)�� N Ϊ���򼯵Ļ������� M Ϊ������Ļ�����
			* ����ֵ:
			* ָ�������ڣ����� score ֵ(��ѡ)�����򼯳�Ա���б�
			*/
			reply srotedSet::zrange(const std::string& key, int start = 0, int stop = -1, bool withScores = true );

			/**
			* �������� key �У����� score ֵ���� min �� max ֮��(�������� min �� max )�ĳ�Ա�����򼯳�Ա�� score ֵ����(��С����)�������С�
			* ������ͬ score ֵ�ĳ�Ա���ֵ���(lexicographical order)������(�������������ṩ�ģ�����Ҫ����ļ���)��
			* ��ѡ�� LIMIT ����ָ�����ؽ��������������(����SQL�е� SELECT LIMIT offset, count )��ע�⵱ offset �ܴ�ʱ����λ offset
			* �Ĳ���������Ҫ�����������򼯣��˹�������Ӷ�Ϊ O(N) ʱ�䡣
			* ��ѡ�� WITHSCORES ��������������ǵ����������򼯵ĳ�Ա�����ǽ����򼯳�Ա���� score ֵһ�𷵻ء�
			* ��ѡ���� Redis 2.0 �汾����á�
			* ���估����
			* min �� max ������ -inf �� +inf ������һ������Ϳ����ڲ�֪�����򼯵���ͺ���� score ֵ������£�ʹ�� ZRANGEBYSCORE �������
			* Ĭ������£������ȡֵʹ�ñ����� (С�ڵ��ڻ���ڵ���)����Ҳ����ͨ��������ǰ���� ( ������ʹ�ÿ�ѡ�Ŀ����� (С�ڻ����)��
			* �ٸ����ӣ�
			* ZRANGEBYSCORE zset (1 5
			* �������з������� 1 < score <= 5 �ĳ�Ա����
			* ZRANGEBYSCORE zset (5 (10
			* �򷵻����з������� 5 < score < 10 �ĳ�Ա��
			*
			* ���ð汾��>= 1.0.5
			* ʱ�临�Ӷ�:O(log(N)+M)�� N Ϊ���򼯵Ļ����� M Ϊ��������Ļ�����
			* ����ֵ:ָ�������ڣ����� score ֵ(��ѡ)�����򼯳�Ա���б�
			*/
			reply zrangebyscore(const std::string& key, 
				const std::string& min = "-inf", 
				const std::string& max = "+inf",
				bool withScores = true,
				const std::string& limit = "");

			/**
			* �������� key �г�Ա member ���������������򼯳�Ա�� score ֵ����(��С����)˳�����С�
			* ������ 0 Ϊ�ף�Ҳ����˵�� score ֵ��С�ĳ�Ա����Ϊ 0 ��
			* ʹ�� ZREVRANK ������Ի�ó�Ա�� score ֵ�ݼ�(�Ӵ�С)���е�������
			* ���ð汾��>= 2.0.0
			* ʱ�临�Ӷ�:O(log(N))
			* ����ֵ:
			* ��� member ������ key �ĳ�Ա������ member ��������
			* ��� member �������� key �ĳ�Ա������ nil ��
			*/
			reply zrank(const std::string& key, const std::string& member);

			/**
			* �Ƴ����� key �е�һ��������Ա�������ڵĳ�Ա�������ԡ�
			* �� key ���ڵ�������������ʱ������һ������
			* ���ð汾��>= 1.2.0
			* ʱ�临�Ӷ�:O(M*log(N))�� N Ϊ���򼯵Ļ����� M Ϊ���ɹ��Ƴ��ĳ�Ա��������
			* ����ֵ:���ɹ��Ƴ��ĳ�Ա�������������������Եĳ�Ա��
			*/
			long long zrem(const std::string& key, const std::list<std::string>& members);

			/**
			* �Ƴ����� key �У�ָ������(rank)�����ڵ����г�Ա��
			* ����ֱ����±���� start �� stop ָ�������� start �� stop ���ڡ�
			* �±���� start �� stop ���� 0 Ϊ�ף�Ҳ����˵���� 0 ��ʾ���򼯵�һ����Ա���� 1 ��ʾ���򼯵ڶ�����Ա���Դ����ơ�
			* ��Ҳ����ʹ�ø����±꣬�� -1 ��ʾ���һ����Ա�� -2 ��ʾ�����ڶ�����Ա���Դ����ơ�
			* ���ð汾��>= 2.0.0
			* ʱ�临�Ӷ�:O(log(N)+M)�� N Ϊ���򼯵Ļ������� M Ϊ���Ƴ���Ա��������
			* ����ֵ:���Ƴ���Ա��������
			*/
			long long zremrangebyrank(const std::string& key, int start = 0, int stop = -1);

			/**
			* �Ƴ����� key �У����� score ֵ���� min �� max ֮��(�������� min �� max )�ĳ�Ա��
			* ���ð汾��>= 1.2.0
			* ʱ�临�Ӷ�:O(log(N)+M)�� N Ϊ���򼯵Ļ������� M Ϊ���Ƴ���Ա��������
			* ����ֵ:���Ƴ���Ա��������
			*/
			long long zremrangebyscore(const std::string& key, const std::string& min = "-inf", const std::string& max = "+inf");

			/**
			* �������� key �У�ָ�������ڵĳ�Ա��
			* ���г�Ա��λ�ð� score ֵ�ݼ�(�Ӵ�С)�����С�
			* ������ͬ score ֵ�ĳ�Ա���ֵ��������(reverse lexicographical order)���С�
			* ���˳�Ա�� score ֵ�ݼ��Ĵ���������һ���⣬ ZREVRANGE �������������� ZRANGE ����һ����
			* ���ð汾��>= 1.2.0
			* ʱ�临�Ӷ�:O(log(N)+M)�� N Ϊ���򼯵Ļ������� M Ϊ������Ļ�����
			* ����ֵ:ָ�������ڣ����� score ֵ(��ѡ)�����򼯳�Ա���б�
			*/
			reply zrevrange(const std::string& key, int start = 0, int stop = -1, bool withScores = true);

			/**
			* �������� key �У� score ֵ���� max �� min ֮��(Ĭ�ϰ������� max �� min )�����еĳ�Ա�����򼯳�Ա�� score ֵ�ݼ�(�Ӵ�С)�Ĵ������С�
			* ������ͬ score ֵ�ĳ�Ա���ֵ��������(reverse lexicographical order )���С�
			* ���˳�Ա�� score ֵ�ݼ��Ĵ���������һ���⣬ ZREVRANGEBYSCORE �������������� ZRANGEBYSCORE ����һ����
			* ���ð汾��>= 2.2.0
			* ʱ�临�Ӷ�:O(log(N)+M)�� N Ϊ���򼯵Ļ����� M Ϊ������Ļ�����
			* ����ֵ:ָ�������ڣ����� score ֵ(��ѡ)�����򼯳�Ա���б�
			*/
			reply zrevrangebyscore(const std::string& key, 
				const std::string& max = "+inf", 
				const std::string& min = "-inf",
				bool withScores = true,
				const std::string& limit = "");

			/**
			* �������� key �г�Ա member ���������������򼯳�Ա�� score ֵ�ݼ�(�Ӵ�С)����
			* ������ 0 Ϊ�ף�Ҳ����˵�� score ֵ���ĳ�Ա����Ϊ 0 ��
			* ʹ�� ZRANK ������Ի�ó�Ա�� score ֵ����(��С����)���е�������
			* ���ð汾��>= 2.0.0
			* ʱ�临�Ӷ�:O(log(N))
			* ����ֵ:
			* ��� member ������ key �ĳ�Ա������ member ��������
			* ��� member �������� key �ĳ�Ա������ nil ��
			*/
			reply zrevrank(const std::string& key, const std::string& member);

			/**
			* �������� key �У���Ա member �� score ֵ��
			* ��� member Ԫ�ز������� key �ĳ�Ա���� key �����ڣ����� nil ��
			* ���ð汾��>= 1.2.0
			* ʱ�临�Ӷ�:O(1)
			* ����ֵ:member ��Ա�� score ֵ�����ַ�����ʽ��ʾ��
			*/
			std::string zscore(const std::string& key, const std::string& member);

			/**
			* ���������һ���������򼯵Ĳ��������и��� key ������������ numkeys ����ָ���������ò���(�����)���浽 destination ��
			* Ĭ������£��������ĳ����Ա�� score ֵ�����и������¸ó�Ա score ֵ֮ �� ��
			* WEIGHTS
			* ʹ�� WEIGHTS ѡ������Ϊ ÿ�� �������� �ֱ� ָ��һ���˷�����(multiplication factor)��
			* ÿ���������򼯵����г�Ա�� score ֵ�ڴ��ݸ��ۺϺ���(aggregation function)֮ǰ��Ҫ�ȳ��Ը����򼯵����ӡ�
			* ���û��ָ�� WEIGHTS ѡ��˷�����Ĭ������Ϊ 1 ��
			* AGGREGATE
			* ʹ�� AGGREGATE ѡ������ָ�������Ľ�����ľۺϷ�ʽ��
			* Ĭ��ʹ�õĲ��� SUM �����Խ����м�����ĳ����Ա�� score ֵ֮ �� ��Ϊ������иó�Ա�� score ֵ��ʹ�ò��� MIN �����Խ����м���
			* ��ĳ����Ա�� ��С score ֵ��Ϊ������иó�Ա�� score ֵ�������� MAX ���ǽ����м�����ĳ����Ա�� ��� score ֵ��Ϊ������и�
			* ��Ա�� score ֵ��
			* ���ð汾��>= 2.0.0
			* ʱ�临�Ӷ�:O(N)+O(M log(M))�� N Ϊ�������򼯻������ܺͣ� M Ϊ������Ļ�����
			* ����ֵ:���浽 destination �Ľ�����Ļ�����
			*/
			long long zunionstore(const std::string& destination,long long numkeys,
				const std::list<std::string>& keys,
				const std::list<std::string>& weights = {},
				const std::string& aggregate = "");

			/*
			* ���������һ���������򼯵Ľ��������и��� key ������������ numkeys ����ָ���������ý���(�����)���浽 destination ��
			* Ĭ������£��������ĳ����Ա�� score ֵ�����и������¸ó�Ա score ֵ֮��.
			* ���ð汾��>= 2.0.0
			* ʱ�临�Ӷ�:
			* O(N*K)+O(M*log(M))�� N Ϊ���� key �л�����С�����򼯣� K Ϊ�������򼯵������� M Ϊ������Ļ�����
			* ����ֵ:
			* ���浽 destination �Ľ�����Ļ�����
			*/
			long long zinterstore(const std::string& destination, long long numkeys,
				const std::list<std::string>& keys,
				const std::list<std::string>& weights = {},
				const std::string& aggregate = "");


			reply zscan(const std::string& key, int cursor = 0, const std::string& matchPattern = "*", int count = 10);

			/**
			* �����򼯺ϵ����г�Ա��������ͬ�ķ�ֵʱ�� ���򼯺ϵ�Ԫ�ػ���ݳ�Ա���ֵ���lexicographical ordering������������ �������
			* ������Է��ظ��������򼯺ϼ� key �У� ֵ���� min �� max ֮��ĳ�Ա��
			* ������򼯺�����ĳ�Ա���в�ͬ�ķ�ֵ�� ��ô����صĽ����δָ���ģ�unspecified����
			* �����ʹ�� C ���Ե� memcmp() ������ �Լ����е�ÿ����Ա��������ֽڵĶԱȣ�byte-by-byte compare���� �����մӵ͵��ߵ�˳��
			* ���������ļ��ϳ�Ա�� ��������ַ�����һ������������ͬ�Ļ��� ��ô�������Ϊ�ϳ����ַ����Ƚ϶̵��ַ���Ҫ��
			* ��ѡ�� LIMIT offset count �������ڻ�ȡָ����Χ�ڵ�ƥ��Ԫ�� ������ SQL �е� SELECT LIMIT offset count ��䣩�� ��Ҫע��
			* ��һ���ǣ� ��� offset ������ֵ�ǳ���Ļ��� ��ô�����ڷ��ؽ��֮ǰ�� ��Ҫ�ȱ����� offset ��ָ����λ�ã� ���������Ϊ�����
			* ����� O(N) ���Ӷȡ�
			* ���ָ����Χ����
			* �Ϸ��� min �� max ����������� ( ���� [ �� ���� ( ��ʾ�����䣨ָ����ֵ���ᱻ�����ڷ�Χ֮�ڣ��� �� [ ���ʾ�����䣨ָ����ֵ��
			* �������ڷ�Χ֮�ڣ���
			* ����ֵ + �� - �� min �����Լ� max �����о�����������壬 ���� + ��ʾ�����ޣ� �� - ��ʾ�����ޡ� ��ˣ� ��һ�����г�Ա�ķ�ֵ����
			* ͬ�����򼯺Ϸ������� ZRANGEBYLEX <zset> - + �� ����������򼯺��е�����Ԫ�ء�
			* ���ð汾��>= 2.8.9
			* ʱ�临�Ӷȣ�
			* O(log(N)+M)�� ���� N Ϊ���򼯺ϵ�Ԫ�������� �� M ��������ص�Ԫ�������� 
			* ��� M ��һ������������˵���û�����ʹ�� LIMIT �������������ȵ� 10 ��Ԫ�أ��� ��ô����ĸ��Ӷ�Ҳ���Կ����� O(log(N)) ��
			* ����ֵ��
			* ����ظ���һ���б��б�������������򼯺���ָ����Χ�ڵĳ�Ա��
			*/
			reply zrangebylex(const std::string& key, 
				const std::string& min = "-inf", 
				const std::string& max = "+inf",
				const std::string& limit = "");

			/**
			* ����һ�����г�Ա�ķ�ֵ����ͬ�����򼯺ϼ� key ��˵�� �������᷵�ظü����У� ��Ա���� min �� max ��Χ�ڵ�Ԫ��������
			* �������� min ������ max ����������� ZRANGEBYLEX ����� min ������ max ����������һ����
			* ���ð汾��>= 2.8.9
			* ʱ�临�Ӷȣ�O(log(N))������ N Ϊ���򼯺ϰ�����Ԫ��������
			* ����ֵ�������ظ���ָ����Χ�ڵ�Ԫ��������
			*/
			long long zlexcount(const std::string& key,
				const std::string& min = "-inf",
				const std::string& max = "+inf");
			/**
			* ����һ�����г�Ա�ķ�ֵ����ͬ�����򼯺ϼ� key ��˵�� ���������Ƴ��ü����У� ��Ա���� min �� max ��Χ�ڵ�����Ԫ�ء�
			* �������� min ������ max ����������� ZRANGEBYLEX ����� min ������ max ����������һ����
			* ���ð汾��>= 2.8.9
			* ʱ�临�Ӷȣ�O(log(N)+M)�� ���� N Ϊ���򼯺ϵ�Ԫ�������� �� M ��Ϊ���Ƴ���Ԫ��������
			* ����ֵ�������ظ������Ƴ���Ԫ��������
			*/
			long long zremrangebylex(const std::string& key,
				const std::string& min = "-inf",
				const std::string& max = "+inf");
		private:
			client& cli_;
		};
	};
};

#if !defined(CORE_ONLY_HEADER)
#include "impl/sroted_set.hpp"
#endif

#endif