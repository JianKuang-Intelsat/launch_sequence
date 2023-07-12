#include <iostream>
#include <functional>
#include <string>
#include <thread>
#include "funcs.h"
#include "event.h"

using namespace std::this_thread;
// Function template for any function signature

launch_funcs::Event::Event(string name, int t, int (*a)(map<string, char>& check_event)) {
	identifier = name;
	t_minus = t;
	action = a;
	seconds_until_next = 0;
	next_event = NULL;
}

int launch_funcs::Event::execute(map<string, char>& check_events) {
	return action(check_events);
}

int launch_funcs::Event::count_until_next() {
	for(long int i = 0; i < seconds_until_next; i++ ) {
		cout << "\r" << t_minus - i << " " << endl;
		sleep_for(1s);
	}
	return 0;
}
