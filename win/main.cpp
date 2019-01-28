#include <iostream>

#include "redis/client.hpp"
#include "redis/op/set.hpp"
#include "redis/op/string.hpp"
#include "redis/op/hash.hpp"
#include "redis/op/key.hpp"



int main()
{
	try
	{
		redis::client cli;
		cli.connect("192.168.1.30", 6379);

		redis::op::key k(cli);
		k.type("ff");

		redis::op::hash h(cli);
		h.vals("gg");
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	

	system("pause");
	return 0;
}
