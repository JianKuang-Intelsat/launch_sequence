#include <iostream>
#include <functional>
#include <string>
#include <thread>
#include "funcs.h"
#include "event.h"
#include "checkpoint.h"

using namespace std::this_thread;

launch_funcs::Checkpoint::Checkpoint(string name, int t, int (*a)(map<string, char>& check_events), std::chrono::system_clock::time_point target_launch) : Event(name, t, a) {
	identifier = name;
	target_check = target_launch;
	t_minus = t;
	action = a;
	seconds_until_next = 0;
	adjustment = 0; // milliseconds 
	next_event = NULL;
}

int launch_funcs::Checkpoint::execute(map<string, char>& check_events) {
	return action(check_events);
}

int launch_funcs::Checkpoint::count_until_next() {
	auto now = std::chrono::system_clock::now();
	adjustment = std::chrono::duration_cast<std::chrono::milliseconds>(target_check - now).count() - 1000 * (t_minus - 1);
	cout << t_minus << " Checkpoint passed" << endl;
	cout << (1000 - adjustment) << " milliseconds adjusted" << endl;
	sleep_for(std::chrono::milliseconds(adjustment));
	for(long int i = 1; i < seconds_until_next; i++ ) {
		cout << t_minus - i << " " << endl;
		sleep_for(1s);
	}
	return 0;
}
