#include <iostream>
#include <functional>
#include <string>
#include <thread>
#include "funcs.h"
#include "event.h"
#include "checkpoint.h"

using namespace std::this_thread;

launch_funcs::Checkpoint::Checkpoint(string name, int t, std::chrono::system_clock::time_point target_launch) : Event(name, t) {
	std::map<std::string, int (*)(std::map<std::string, char>&)> func_map = FunctionMap::getInstance().func_map;
	identifier = name;
	target_check = target_launch;
	t_minus = t;
	seconds_until_next = 0;
	adjustment = 0; // milliseconds 
	next_event = NULL;
	action = func_map[identifier];
}

int launch_funcs::Checkpoint::execute(map<string, char>& check_events) {
	return action(check_events);
}

int launch_funcs::Checkpoint::count_until_next() {
	int second, minute;
	auto now = std::chrono::system_clock::now();
	minute = t_minus / 60;
	second = t_minus - 60 * minute;
	adjustment = std::chrono::duration_cast<std::chrono::milliseconds>(target_check - now).count() - 1000 * (t_minus - 1);
	cout << "T-" << minute << ":" << second << " Checkpoint passed" << endl;
	cout << (1000 - adjustment) << " milliseconds adjusted" << endl;
	sleep_for(std::chrono::milliseconds(adjustment));
	for(long int i = 1; i < seconds_until_next; i++ ) {
		second = t_minus - i;
		minute = second / 60;
		second = second - 60 * minute;
		cout << "\r" << "T-" << minute << ":" << second << " ";
		cout.flush();
		sleep_for(1s);
	}
	cout << endl;
	return 0;
}
