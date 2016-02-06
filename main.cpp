/*
 * main.cpp
 *
 *  Created on: Feb 6, 2016
 *      Author: armin
 */

#include <iostream>
#include "Controller.h"

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
