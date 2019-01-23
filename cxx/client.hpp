

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