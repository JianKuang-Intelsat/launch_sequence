#include <iostream>
#include <functional>
#include <string>
#include <thread>
#include <map>
#include "funcs.h"
#include "event.h"

using namespace std::this_thread;
// Function template for any function signature

launch_funcs::Event::Event(string name, int t) {
	std::map<std::string, int (*)(std::map<std::string, char>&)> func_map = FunctionMap::getInstance().func_map;
	identifier = name;
	etype = "ordinary";
	t_minus = t;
	seconds_until_next = 0;
	next_event = NULL;
	action = func_map[identifier];
}

int launch_funcs::Event::execute(map<string, char>& check_events) {
	return action(check_events);
}

int launch_funcs::Event::count_until_next() {
	int second, minute;
	for(long int i = 0; i < seconds_until_next; i++ ) {
		second = t_minus - i;
		minute = second / 60;
		second = second - 60 * minute;
		//cout << "\r" << "T-" << minute << ":" << second << " ";
		printf(BOLD "\r T-%02d:%02d " RESET, minute, second);
		cout.flush();
		sleep_for(1s);
	}
	cout << endl;
	return 0;
}
