
#ifndef _CXXREDIS_CONNECTION_IMPL_HPP_
#define _CXXREDIS_CONNECTION_IMPL_HPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <sys/types.h>
#ifndef _WIN32
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <fcntl.h>
#include <errno.h>

typedef int SOCKET;
#define SOCKET_ERROR (-1)

#else

#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")

#endif
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

#ifdef _WIN32
#define SETERRNO errnox = WSAGetLastError()
#undef errno
int errnox = EINPROGRESS;
#define errno errnox
#else
#define SETERRNO
#endif

#define SOCKET_SUCCESS 0

#include "redis/cxx/exception.hpp"

#define THROW_SOCKET_IO_ERROR { SETERRNO; throw exception(exception::errorCode::SOCKET_IO_ERROR, strerror(errno));}

namespace CXXRedis {

	class connectionImpl {
	public:
		connectionImpl()
		{
#ifdef _WIN32

			WORD wVersionRequested = MAKEWORD(2, 0);
			WSADATA wsaData;

			if (WSAStartup(wVersionRequested, &wsaData) != SOCKET_SUCCESS) THROW_SOCKET_IO_ERROR;
#endif
			fd_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			if (fd_ == SOCKET_ERROR) THROW_SOCKET_IO_ERROR;

		}
		~connectionImpl()
		{

#ifdef _WIN32
			WSACleanup();
			closesocket(fd_);
#else
			close(fd_);
#endif
		}

		void connect(const std::string& host, int port)
		{
			struct sockaddr_in addr;

			memset(&addr, 0, sizeof(addr));
			addr.sin_family = AF_INET;
			addr.sin_port = ::htons(port);
			addr.sin_addr.s_addr = resolvHost(host);

			if (::connect(fd_, (sockaddr*)&addr, sizeof(sockaddr_in)) != SOCKET_SUCCESS) THROW_SOCKET_IO_ERROR;
		}

		void send(const void* buff, size_t bytes)
		{
			size_t sendBytes = 0;

			while (true)
			{
				int n = ::send(fd_, (const char*)buff + sendBytes, bytes - sendBytes, 0);

				if (n == SOCKET_ERROR)
				{
					if (errno == EAGAIN) {}
					else THROW_SOCKET_IO_ERROR;
				}
				sendBytes += n;

				if (sendBytes == bytes) break;
			}

		}
		std::string read()
		{
			char buffer[1024 * 16];
			int n = ::recv(fd_, buffer, sizeof(buffer), 0);

			if (n == SOCKET_ERROR)
			{
				if (errno == EAGAIN)
				{
					return std::string();
				}
				else THROW_SOCKET_IO_ERROR;
			}
			else if (n == 0) throw exception(exception::errorCode::SCOKET_IO_EOF, "remote host force close connection");

			return std::string(buffer, n);
		}

	private:
		uint32_t resolvHost(const std::string& host)
		{
			uint32_t trial;
#ifndef _WIN32
			if (inet_aton(ip.c_str(), (struct in_addr*)&trial) != 0)
#else
			if ((trial = inet_addr(host.c_str())) != INADDR_NONE)
#endif
			{
				return trial;
			}

			struct hostent * hosts = gethostbyname(host.c_str());
			if (hosts != NULL)
			{
				trial = *(uint32_t*)(hosts->h_addr_list[0]);
				return trial;
			}

			throw exception(exception::errorCode::SOCKET_IO_ERROR, "resolvHost error");
		}
	private:
		SOCKET fd_;
	};
}
#endif