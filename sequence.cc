#include <iostream>
#include <functional>
#include <ctime>
#include <string>
#include <chrono>
#include <thread>
#include <map>
#include "funcs.h"
#include "sequence.h"

using namespace std;

launch_funcs::Sequence::Sequence(int year, int month, int day, int hour, int minute, int second, int millisecond)
{
	std::tm future_time_tm = {};
	future_time_tm.tm_year = year - 1900;  // years since 1900
	future_time_tm.tm_mon = month - 1;     // months since January (0-11)
	future_time_tm.tm_mday = day;          // day of the month (1-31)
	future_time_tm.tm_hour = hour;         // hours since midnight (0-23)
	future_time_tm.tm_min = minute;        // minutes after the hour (0-59)
	future_time_tm.tm_sec = second;        // seconds after the minute (0-60)
	future_time_tm.tm_isdst = 0;            // time district is UTC

	Event* lift_off = new Event("lift_off", 0);		// last event
	std::time_t future_time_t = timegm(&future_time_tm);			// convert tm structure into time_t
	auto future_time_point = std::chrono::system_clock::from_time_t(future_time_t);	// set clock
	future_time_point += std::chrono::milliseconds(millisecond);		// adjust by milliseconds
	target_launch = future_time_point;					// target launch time
	check_events = {};			// the status of all past events
	current_event = lift_off;		// pointer, to the last event

	check_status_display = {{CHECK_GO,"GO"}, {CHECK_NOGO, "NOGO"}};
}

int launch_funcs::Sequence::add_event(Event* new_event) {
	long int seconds, remaining;
	auto now = std::chrono::system_clock::now();
	remaining = new_event -> t_minus;
	new_event -> next_event = current_event;
	new_event -> seconds_until_next = new_event -> t_minus - current_event -> t_minus;
	check_events[new_event -> identifier] = NOT_RUN;
	current_event = new_event;
	return STATUS_NOMINAL;
}

int launch_funcs::Sequence::start_countdown() {
	long int seconds, remaining;
	int run_status;
	auto now = std::chrono::system_clock::now();
	seconds = std::chrono::duration_cast<std::chrono::seconds>(target_launch - now).count();
	remaining = seconds - current_event -> t_minus;		// remaining seconds until the next scheduled event
	if(remaining < 0){
		cout << "Insufficient time remaining!" << endl;	// Please set a further target launch into the future
		return MALFUNCTION;
	}
	Event* pre_start = new Event("pre_start", seconds);
	pre_start -> seconds_until_next = remaining;
	pre_start -> next_event = current_event;
	current_event = pre_start;
	cout << "Count down initiated!" << endl;
	while(current_event -> next_event != NULL) { 
		std::thread t([this]() {
			return current_event -> execute(check_events);	// create another thread to run the action
		});
		t.detach();
									// async programming
		if(current_event -> identifier == "final_check") {
			current_event -> execute(check_events);  // run the final check in the main thread
			for(const auto &pair : check_events) {
				cout << "Process " << pair.first << " status " << check_status_display[pair.second] << endl;
			}
			if(check_events[current_event -> identifier] != CHECK_GO) {
				cout << "Launch Aborted!" << endl;
				return MALFUNCTION;		// final check, all events should be GO at this moment, 
								// otherwise, abort
			}
		}
		current_event -> count_until_next();
		current_event = current_event -> next_event;
	}
	current_event -> execute(check_events);
	return STATUS_NOMINAL;
}
