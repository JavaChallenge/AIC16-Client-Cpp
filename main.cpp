//
// client.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2014 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>

#include "Controller.h"

using boost::asio::ip::tcp;

int main() {
	setbuf(stdout, NULL);

	try {
		Controller *control = new Controller("connection.conf");
		control->start();
	} catch (std::exception& e) {
		std::cerr << "MAIN EXCEPTION\n";
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
