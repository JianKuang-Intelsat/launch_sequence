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
			map<string, char> check_events;
			Event* current_event;
	
			Sequence(int year, int month, int day, int hour, int minute, int second, int millisecond);
	
			int add_event(Event* new_event);

			int build_sequence();
	
			int start_countdown();
	};
}

#endif
