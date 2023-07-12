#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <map>
#include "checkpoint.h"
#include "event.h"

using namespace std;

namespace launch_funcs {

	class Sequence {
	
		public:
			std::chrono::system_clock::time_point target_launch;
			map<string, char> check_events;		// milestone events, example: engin_chill. GO/NOGO;
			map<string, char> continuous_monitor;	// continuous monitoring states, example: weather, range. GO/NOGO;
			map<char, string> check_status_display;
			Event* current_event;		// pointer to the earliest event in sequence, initialized to "lift_off"
	
			Sequence(int year, int month, int day, int hour, int minute, int second, int millisecond);
	
			int add_event(Event* new_event);

			int build_sequence();
	
			int start_countdown();
	};
}

#endif
