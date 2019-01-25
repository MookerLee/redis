
#ifndef _CXXREDIS_OP_STRING_HPP_
#define _CXXREDIS_OP_STRING_HPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <string>

namespace CXXRedis {

	class client;
	class reply;

	namespace op {

		class string {

		public:
			string(client& cli);
			~string();

			/**
			* ��� key �Ѿ����ڲ�����һ���ַ����� APPEND ��� value ׷�ӵ� key ԭ����ֵ��ĩβ��
			* ��� key �����ڣ� APPEND �ͼ򵥵ؽ����� key ��Ϊ value ������ִ�� SET key value һ����
			* ���ð汾��>= 2.0.0
			* ʱ�临�Ӷȣ�ƽ̯O(1)
			* ����ֵ��׷�� value ֮�� key ���ַ����ĳ��ȡ�
			*/
			long long append(const std::string& key, const std::string& appStr);
			/**
			* ��������ַ����У�������Ϊ 1 �ı���λ��������
			* һ������£������������ַ������ᱻ���м�����ͨ��ָ������� start �� end �����������ü���ֻ���ض���λ�Ͻ��С�
			* start �� end ���������ú� GETRANGE �������ƣ�������ʹ�ø���ֵ������ -1 ��ʾ���һ��λ���� -2 ��ʾ�����ڶ���λ���Դ����ơ�
			* �����ڵ� key �������ǿ��ַ�����������˶�һ�������ڵ� key ���� BITCOUNT ���������Ϊ 0 ��
			* ���ð汾��>= 2.6.0
			* ʱ�临�Ӷȣ�O(N)
			* ����ֵ��������Ϊ 1 ��λ��������
			*/
			long long bitCount(const std::string& key, int start = 0, int end = -1);

			/**
			* ��һ���������������λ���ַ��� key ����λԪ����������������浽 destkey �ϡ�
			* operation ������ AND �� OR �� NOT �� XOR �����ֲ����е�����һ�֣�
			* BITOP AND destkey key [key ...] ����һ������ key ���߼���������������浽 destkey ��
			* BITOP OR destkey key [key ...] ����һ������ key ���߼��򣬲���������浽 destkey ��
			* BITOP XOR destkey key [key ...] ����һ������ key ���߼���򣬲���������浽 destkey ��
			* BITOP NOT destkey key ���Ը��� key ���߼��ǣ�����������浽 destkey ��
			* ���� NOT ����֮�⣬�������������Խ���һ������ key ��Ϊ���롣
			* �� BITOP ����ͬ���ȵ��ַ���ʱ���϶̵��Ǹ��ַ�����ȱ�ٵĲ��ֻᱻ���� 0 ��
			* �յ� key Ҳ�������ǰ��� 0 ���ַ������С�
			* ���ð汾��>= 2.6.0
			* ʱ�临�Ӷȣ�O(N)
			* ����ֵ�����浽 destkey ���ַ����ĳ��ȣ������� key ������ַ���������ȡ�
			*/
			template <class... Args>
			long long bitOP(const std::string& subCmd, const std::string& destkey, Args... keys);

			template <class... Args>
			long long bitOPAnd(const std::string& destkey, Args... keys);

			template <class... Args>
			long long bitOPOr(const std::string& destkey, Args... keys);

			template <class... Args>
			long long bitOPXor(const std::string& destkey, Args... keys);

			long long bitOPNot(const std::string& destkey, const std::string& key);

			/**
			* �� key ��������ַ���ֵ����ȡָ��ƫ�����ϵ�λ(bit)��
			* �� offset ���ַ���ֵ�ĳ��ȴ󣬻��� key ������ʱ������ 0 ��
			* ���ð汾��>= 2.2.0
			* ʱ�临�Ӷȣ�O(1)
			* ����ֵ���ַ���ֵָ��ƫ�����ϵ�λ(bit)��
			*/
			long long getBit(const std::string& key, int offset);

			/**
			* �� key ��������ַ���ֵ�����û����ָ��ƫ�����ϵ�λ(bit)��
			* λ�����û����ȡ���� value ������������ 0 Ҳ������ 1 ��
			* �� key ������ʱ���Զ�����һ���µ��ַ���ֵ��
			* �ַ����������չ(grown)��ȷ�������Խ� value ������ָ����ƫ�����ϡ����ַ���ֵ������չʱ���հ�λ���� 0 ��䡣
			* offset ����������ڻ���� 0 ��С�� 2^32 (bit ӳ�䱻������ 512 MB ֮��)��
			* ����ֵ��ָ��ƫ����ԭ�������λ
			* ���ð汾��>= 2.2.0
			*/
			long long setBit(const std::string& key, int offset, int bit);
			/**
			* �� key �д��������ֵ��һ��
			* ��� key �����ڣ���ô key ��ֵ���ȱ���ʼ��Ϊ 0 ��Ȼ����ִ�� DECR ������
			* ���ֵ������������ͣ����ַ������͵�ֵ���ܱ�ʾΪ���֣���ô����һ������
			* ��������ֵ������ 64 λ(bit)�з������ֱ�ʾ֮�ڡ�
			* ���ð汾��>= 1.0.0
			* ʱ�临�Ӷȣ�O(1)
			* ����ֵ��ִ�� DECR ����֮�� key ��ֵ��
			*/
			long long decr(const std::string& key);
			
			/**
			* �� key �������ֵ��ȥ���� decrement ��
			* ��� key �����ڣ���ô key ��ֵ���ȱ���ʼ��Ϊ 0 ��Ȼ����ִ�� DECRBY ������
			* ���ֵ������������ͣ����ַ������͵�ֵ���ܱ�ʾΪ���֣���ô����һ������
			* ��������ֵ������ 64 λ(bit)�з������ֱ�ʾ֮�ڡ�
			* ���ð汾��>= 1.0.0
			* ʱ�临�Ӷȣ�O(1)
			* ����ֵ����ȥ decrement ֮�� key ��ֵ��
			*/
			long long decrBy(const std::string& key, long long decrement);
			
			/**
			* �� key �д��������ֵ��һ��
			* ��� key �����ڣ���ô key ��ֵ���ȱ���ʼ��Ϊ 0 ��Ȼ����ִ�� INCR ������
			* ���ֵ������������ͣ����ַ������͵�ֵ���ܱ�ʾΪ���֣���ô����һ������
			* ��������ֵ������ 64 λ(bit)�з������ֱ�ʾ֮�ڡ�
			* ���ð汾��>= 1.0.0
			* ʱ�临�Ӷȣ�O(1)
			* ����ֵ��ִ�� INCR ����֮�� key ��ֵ��
			*/
			long long incr(const std::string& key);

			/**
			* �� key �������ֵ�������� increment ��
			* ��� key �����ڣ���ô key ��ֵ���ȱ���ʼ��Ϊ 0 ��Ȼ����ִ�� INCRBY ���
			* ���ֵ������������ͣ����ַ������͵�ֵ���ܱ�ʾΪ���֣���ô����һ������
			* ��������ֵ������ 64 λ(bit)�з������ֱ�ʾ֮�ڡ�
			* ���ð汾��>= 1.0.0
			* ʱ�临�Ӷȣ�O(1)
			* ����ֵ������ increment ֮�� key ��ֵ��
			*/
			long long incrBy(const std::string& key, long long increment);

			/**
			* Ϊ key ���������ֵ���ϸ��������� increment ��
			* ��� key �����ڣ���ô INCRBYFLOAT ���Ƚ� key ��ֵ��Ϊ 0 ����ִ�мӷ�������
			* �������ִ�гɹ�����ô key ��ֵ�ᱻ����Ϊ��ִ�мӷ�֮��ģ���ֵ��������ֵ�����ַ�������ʽ���ظ������ߡ�
			*
			* ������ key ��ֵ���������� increment ��
			* ������ʹ���� 2.0e7 �� 3e5 �� 90e-2 ������ָ������(exponential notation)����ʾ��
			* ���ǣ�ִ�� INCRBYFLOAT ����֮���ֵ������ͬ������ʽ���棬Ҳ���ǣ�
			* ����������һ�����֣�һ������ѡ�ģ�С�����һ������λ��С��������ɣ����� 3.14 �� 69.768 ���������)��
			* С������β��� 0 �ᱻ�Ƴ����������Ҫ�Ļ������Ὣ��������Ϊ���������� 3.0 �ᱻ����� 3 ����
			*
			* ����֮�⣬���ۼӷ��������õĸ�������ʵ�ʾ����ж೤�� INCRBYFLOAT �ļ�����Ҳ���ֻ�ܱ�ʾС����ĺ�ʮ��λ��
			*
			* ����������һ����������ʱ������һ������
			* key ��ֵ�����ַ�������(��Ϊ Redis �е����ֺ͸����������ַ�������ʽ���棬�������Ƕ������ַ������ͣ�
			* key ��ǰ��ֵ���߸��������� increment ���ܽ���(parse)Ϊ˫���ȸ�����(double precision floating point number��
			*
			* ���ð汾��>= 2.6.0
			* ʱ�临�Ӷȣ�O(1)
			* ����ֵ��ִ������֮�� key ��ֵ��
			*/
			std::string incrByFloat(const std::string& key, double increment);

			/**
			* ���� key ���������ַ���ֵ��
			* ��� key ��������ô��������ֵ nil ��
			* ���� key �����ֵ�����ַ������ͣ�����һ��������Ϊ GET ֻ�����ڴ����ַ���ֵ��
			*
			* ���ð汾��>= 1.0.0
			* ʱ�临�Ӷȣ�O(1)
			* ����ֵ���� key ������ʱ������ nil �����򣬷��� key ��ֵ����� key �����ַ������ͣ���ô����һ������
			*/
			std::string get(const std::string& key);

			/**
			* ��������(һ������)���� key ��ֵ��
			* ��������� key ���棬��ĳ�� key �����ڣ���ô��� key ��������ֵ nil ����ˣ�����������ʧ�ܡ�
			*
			* ���ð汾��>= 1.0.0
			* ʱ�临�Ӷ�:O(N) , N Ϊ���� key ��������
			* ����ֵ��һ���������и��� key ��ֵ���б�
			*/
			template <class... Args>
			reply mget(Args... keys);

			/**
			* ���� key ���ַ���ֵ�����ַ������ַ����Ľ�ȡ��Χ�� start �� end ����ƫ��������(���� start �� end ����)��
			* ����ƫ������ʾ���ַ������ʼ������ -1 ��ʾ���һ���ַ��� -2 ��ʾ�����ڶ������Դ����ơ�
			* GETRANGE ͨ����֤���ַ�����ֵ��(range)������ʵ���ַ�����ֵ������������Χ��ֵ������
			*
			* �� <= 2.0 �İ汾�GETRANGE ������ SUBSTR��
			* ���ð汾��>= 2.4.0
			*
			* ʱ�临�Ӷȣ�O(N)�� N ΪҪ���ص��ַ����ĳ��ȡ�
			* ���Ӷ��������ַ����ķ���ֵ���Ⱦ�����
			* ����Ϊ�������ַ�����ȡ�����ַ����Ĳ����ǳ�����(cheap)��
			* ���Զ��ڳ��Ȳ�����ַ������ò����ĸ��Ӷ�Ҳ�ɿ���O(1)��
			*
			* ����ֵ����ȡ�ó������ַ�����
			*/
			std::string getRange(const std::string& key,int start = 0,int end = -1);

			/**
			* ������ key ��ֵ��Ϊ value �������� key �ľ�ֵ(old value)��
			* �� key ���ڵ������ַ�������ʱ������һ������
			*
			* ���ð汾��>= 1.0.0
			* ʱ�临�Ӷȣ�O(1)
			* ����ֵ�����ظ��� key �ľ�ֵ���� key û�о�ֵʱ��Ҳ���ǣ� key ������ʱ������ nil ��
			*/
			std::string getSet(const std::string& key, const std::string& newvalue);

			/**
			* ͬʱ����һ������ key-value �ԡ�
			*
			* ���ĳ������ key �Ѿ����ڣ���ô MSET ������ֵ����ԭ���ľ�ֵ������ⲻ������ϣ����Ч����
			* �뿼��ʹ�� MSETNX �����ֻ�������и��� key �������ڵ�����½������ò�����
			*
			* MSET ��һ��ԭ����(atomic)���������и��� key ������ͬһʱ���ڱ����ã�
			* ĳЩ���� key �����¶���һЩ���� key û�иı������������ܷ�����
			*
			* ���ð汾��>= 1.0.1
			* ʱ�临�Ӷȣ�O(N)�� N ΪҪ���õ� key ������
			* ����ֵ�����Ƿ��� OK (��Ϊ MSET ������ʧ��)
			*/
			template <class... Args>
			void mset(std::initializer_list<Args>... pairs);

			/**
			* ͬʱ����һ������ key-value �ԣ����ҽ������и��� key �������ڡ�
			* ��ʹֻ��һ������ key �Ѵ��ڣ� MSETNX Ҳ��ܾ�ִ�����и��� key �����ò�����
			* MSETNX ��ԭ���Եģ�����������������ö����ͬ key ��ʾ��ͬ�ֶ�(field)��Ψһ���߼�����(unique logic object)��
			* �����ֶ�Ҫôȫ�����ã�Ҫôȫ�������á�
			*
			* ���ð汾��>= 1.0.1
			* ʱ�临�Ӷȣ�O(N)�� N ΪҪ���õ� key ��������
			* ����ֵ�������� key ���ɹ����ã����� 1 ��������и��� key ������ʧ��(������һ�� key �Ѿ�����)����ô���� 0 ��
			*/
			template <class... Args>
			bool msetNx(std::initializer_list<Args>... pairs);

			/**
			* �������� SETEX �������ƣ������Ժ���Ϊ��λ���� key ������ʱ�䣬�������� SETEX ��������������Ϊ��λ��
			*
			* ���ð汾��>= 2.6.0
			* ʱ�临�Ӷȣ�O(1)
			* ����ֵ�����óɹ�ʱ���� OK ��
			*/
			void psetEx(const std::string& key, time_t milliseconds, const std::string& value);

			/**
			* ���ַ���ֵ value ������ key ��
			* ��� key �Ѿ���������ֵ�� SET �͸�д��ֵ���������͡�
			* ����ĳ��ԭ����������ʱ�䣨TTL���ļ���˵�� �� SET ����ɹ����������ִ��ʱ�� �����ԭ�е� TTL ���������
			* ��ѡ����
			*
			* �� Redis 2.6.12 �汾��ʼ�� SET �������Ϊ����ͨ��һϵ�в������޸ģ�

			* EX second �����ü��Ĺ���ʱ��Ϊ second �롣 SET key value EX second Ч����ͬ�� SETEX key second value ��
			* PX millisecond �����ü��Ĺ���ʱ��Ϊ millisecond ���롣 SET key value PX millisecond Ч����ͬ�� PSETEX key millisecond value ��
			* NX ��ֻ�ڼ�������ʱ���ŶԼ��������ò����� SET key value NX Ч����ͬ�� SETNX key value ��
			* XX ��ֻ�ڼ��Ѿ�����ʱ���ŶԼ��������ò�����

			* ��Ϊ SET �������ͨ��������ʵ�ֺ� SETNX �� SETEX �� PSETEX ���������Ч�������Խ����� Redis �汾���ܻ�����������Ƴ� SETNX �� SETEX �� PSETEX ���������

			* ���ð汾��>= 1.0.0
			* ʱ�临�Ӷȣ�O(1)
			* ����ֵ��
			* �� Redis 2.6.12 �汾��ǰ�� SET �������Ƿ��� OK ��
			* �� Redis 2.6.12 �汾��ʼ�� SET �����ò����ɹ����ʱ���ŷ��� OK ��
			* ��������� NX ���� XX ������Ϊ����û�ﵽ��������ò���δִ�У���ô����ؿ������ظ���NULL Bulk Reply����
			*/
			void set(const std::string& key, const std::string& value);

			/**
			* ��ֵ value ������ key ������ key ������ʱ����Ϊ seconds (����Ϊ��λ)��
			* ��� key �Ѿ����ڣ� SETEX �����д��ֵ��
			* ��֮ͬ���ǣ� SETEX ��һ��ԭ����(atomic)����������ֵ����������ʱ��������������ͬһʱ������ɣ��������� Redis ��������ʱ���ǳ�ʵ�á�
			* ���ð汾��>= 2.0.0
			* ʱ�临�Ӷȣ�O(1)
			* ����ֵ�����óɹ�ʱ���� OK ���� seconds �������Ϸ�ʱ������һ������
			*/
			void setEx(const std::string& key, time_t seconds, const std::string& value);

			/**
			* �� key ��ֵ��Ϊ value �����ҽ��� key �����ڡ�
			* �������� key �Ѿ����ڣ��� SETNX �����κζ�����
			* SETNX �ǡ�SET if Not eXists��(��������ڣ��� SET)�ļ�д��
			* ���ð汾��>= 1.0.0
			* ʱ�临�Ӷȣ�O(1)
			* ����ֵ�����óɹ������� 1 ������ʧ�ܣ����� 0 ��
			*/
			bool setNx(const std::string& key, const std::string& value);

			/**
			* �� value ������д(overwrite)���� key ��������ַ���ֵ����ƫ���� offset ��ʼ��
			* �����ڵ� key �����հ��ַ�������
			*
			* SETRANGE �����ȷ���ַ����㹻���Ա㽫 value ������ָ����ƫ�����ϣ�
			* ������� key ԭ��������ַ������ȱ�ƫ����С(�����ַ���ֻ�� 5 ���ַ������������õ� offset �� 10 )��
			* ��ôԭ�ַ���ƫ����֮��Ŀհ׽������ֽ�(zerobytes, "\x00" )����䡣
			*
			* ע������ʹ�õ����ƫ������ 2^29-1(536870911) ��
			* ��Ϊ Redis �ַ����Ĵ�С�������� 512 ��(megabytes)���ڡ�
			* �������Ҫʹ�ñ������Ŀռ䣬�����ʹ�ö�� key ��
			*
			* ������һ���ܳ����ַ���ʱ��Redis ��Ҫ�����ڴ�ռ䣬
			* �ò�����ʱ����ܻ���ɷ���������(block)��
			* ��2010���Macbook Pro�ϣ�
			* ����ƫ����Ϊ 536870911(512MB �ڴ����)���ķ�Լ 300 ���룬 
			* ����ƫ����Ϊ 134217728(128MB �ڴ����)���ķ�Լ 80 ���룬����ƫ���� 33554432(32MB �ڴ����)���ķ�Լ 30 ���룬
			* ����ƫ����Ϊ 8388608(8MB �ڴ����)���ķ�Լ 8 ���롣 
			* ע�����״��ڴ����ɹ�֮���ٶ�ͬһ�� key ���� SETRANGE �����������������ڴ档
			*
			* ���ð汾��>= 2.2.0
			*
			* ʱ�临�Ӷȣ���С(small)���ַ�����ƽ̯���Ӷ�O(1)��
			* (����ʲô�ַ����ǡ�С���ģ���ο� APPEND ����)����ΪO(M)�� M Ϊ value �����ĳ��ȡ�
			*
			* ����ֵ���� SETRANGE �޸�֮���ַ����ĳ��ȡ�
			*/
			long long setRange(const std::string& key,int offset, const std::string& value);

			/**
			* ���� key ��������ַ���ֵ�ĳ��ȡ�
			* �� key ����Ĳ����ַ���ֵʱ������һ������
			* ���ð汾��>= 2.2.0
			* ���Ӷȣ�O(1)
			* ����ֵ���ַ���ֵ�ĳ��ȡ��� key ������ʱ������ 0 ��
			*/
			long long strLen(const std::string& key);

		private:
			client& cli_;
		};
	};
};

#if !defined(CORE_ONLY_HEADER)
#include "impl/string.hpp"
#endif

#endif