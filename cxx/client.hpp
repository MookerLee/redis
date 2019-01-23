

#ifndef _REDIS_CLIENT_H_
#define _REDIS_CLIENT_H_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <memory>
#include "format.hpp"

namespace CXXRedis {

	class clientImpl;
	class response;

	class client {

	public:
		class key;
	public:
		client();
		~client();

	   /**
		* @ip	redis��IP��ַ
		* @port redis�Ķ˿�
		* �������ʧ�ܻ��� CXXRedis::exception �쳣
		*/
		void connect(const std::string& ip, int port);
	   /**
		* �ر���redis_server ������
		*/
		void close();
	   /**
	    * @cmd redis����
		* @return_value ����ص�����
		* ������������ CXXRedis::exception �쳣
		*/
		response send(const std::string& cmd);

	   /**
		* @pass redis ����
		* �׳��쳣������֤ʧ���������ر�ʾ�ɹ�
		*/
		void auth(const std::string& pass);
		/**
		* @message echo��Ϣ
		* @return_value ���� @message
		*/
		std::string echo(const std::string& message);

		/**
		* @return_value true ����
		*/
		bool ping();

		void select(int db);
	private:

		// The implementation.
		std::shared_ptr<clientImpl> impl_;
	};

	class client::key{

	public:
		key(client& cli);
		~key();

		template<class... Args>
		int del(Args... keys) 
		{
			return cli_.send(format::formatCmd("DEL", keys...)).asInteger();
		}
		response dump(const std::string& k);
		bool exists(const std::string& k);

	   /**
		* Ϊ���� key ��������ʱ�䣬�� key ����ʱ(����ʱ��Ϊ 0 )�����ᱻ�Զ�ɾ����
		*/
		bool expire(const std::string& k,int second);
	   /**
		* EXPIREAT �����ú� EXPIRE ���ƣ�������Ϊ key ��������ʱ�䡣
		*/
		bool expireat(const std::string& k, time_t timestamp);
	   /**
		* �������з��ϸ���ģʽ pattern �� key 
		*/
		response keys(const std::string& pattern);
		response keys();
	   /**
		* �� key ԭ���Եشӵ�ǰʵ�����͵�Ŀ��ʵ����ָ�����ݿ��ϣ�һ�����ͳɹ��� key ��֤�������Ŀ��ʵ���ϣ�����ǰʵ���ϵ� key �ᱻɾ����
		*/
		void migrate(const std::string& host, int port, const std::string& k, int db, time_t milliseconds);
	   /**
		* ����ǰ���ݿ�� key �ƶ������������ݿ� db ���С�
		*/
		bool move(const std::string& k, int db);
	   /**
		* ���ظ��� key �����������ֵ�Ĵ�������������Ҫ���ڳ���
		*/
		long long objectRefcount(const std::string& k);
		/**
		* ���ظ��� key �Դ��������Ŀ�תʱ��(idle�� û�б���ȡҲû�б�д��)������Ϊ��λ��
		*/
		long long objectIdleTime(const std::string& k);
		/**
		* ���ظ��� key �������ֵ��ʹ�õ��ڲ���ʾ(representation)
		*/
		std::string objectEncoding(const std::string& k);
	private:
		
		
	private:
		client& cli_;
	};
};
#if !defined(CORE_ONLY_HEADER)
#include "impl/client.hpp"
#include "impl/client_key.hpp"
#endif

#endif