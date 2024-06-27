#include <iostream>
#include <thread>
#include <chrono>
#include <boost/asio.hpp>

boost::asio::io_context io_ctx_global;

void task(unsigned int id) {
	std::cout << "task(" << id << ") t_id=" << std::this_thread::get_id() << '\n';
	boost::asio::deadline_timer timer(io_ctx_global, boost::posix_time::millisec(100));
	timer.wait();
	std::cout << "task(" << id << ") finished\n";
}

int main() {
	std::cout << "main() t_id=" << std::this_thread::get_id() << '\n' << '\n';
	try {
		boost::asio::io_context io_context;
		// boost::asio::executor_work_guard<boost::asio::io_context::executor_type> work = boost::asio::make_work_guard(io_context);

		boost::asio::post(io_context, [](){task(0);});
		boost::asio::post(io_context, [](){task(1);});
		boost::asio::post(io_context, [](){task(2);});

		io_context.run();

		boost::asio::post(io_context, [](){task(3);}); // ignored
		boost::asio::post(io_context, [](){task(4);}); // ignored
	} catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}
