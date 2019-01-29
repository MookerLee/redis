#include <iostream>
#include <redis/redis.hpp>

int main()
{
	try
	{
		redis::client cli;
		cli.connect(/*"192.168.1.30", 6379*/);

		cli.sendSimpleCommand("INFO");
		redis::op::string k(cli);
		k.get("ff");

		//redis::op::hash h(cli);
		//h.hvals("gg");

		redis::op::srotedSet st(cli);
		st.zscan("kk");
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	

	system("pause");
	return 0;
}
