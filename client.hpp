

#ifndef _CXXREDIS_CLIENT_HPP_
#define _CXXREDIS_CLIENT_HPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <memory>

namespace redis {

	class clientImpl;
	class reply;

	class client {

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
		reply sendSimpleCommand(const std::string& cmd);

		template<class... Args>
		reply sendSafeCommand(Args... args);

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
};
#if !defined(CORE_ONLY_HEADER)
#include "impl/client.hpp"
#endif

#endif