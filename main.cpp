#include <iostream>
#include <functional>
#include <boost/asio.hpp>

#include <thread>

void print(boost::asio::steady_timer* t, int* count)
{
	if (*count < 5)
	{
		std::cout << "Tick " << *count << '\n';
		++(*count);
		t->expires_at(t->expiry() + boost::asio::chrono::seconds(1));
		t->async_wait(std::bind(print, t, count));
		return;
	}
	std::cout << "Printed after timer is done waiting\n";
}

int main() {
	std::cout << "main() t_id=" << std::this_thread::get_id() << '\n' << '\n';
	try {
		boost::asio::io_context io;

		int count = 0;
		boost::asio::steady_timer t(io, boost::asio::chrono::seconds(1));
		t.async_wait(std::bind(print, &t, &count));

		std::cout << "Print without waiting\n";

		io.run();
		std::cout << "Final count is " << count << '\n';
	} catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << '\n';
	}

	return 0;
}
