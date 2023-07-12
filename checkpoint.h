#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include "event.h"

using namespace std;
// Function template for any function signature

namespace launch_funcs {
	
	class Checkpoint : public Event {

		public:

			chrono::system_clock::time_point target_check;
			int adjustment;
		
			Checkpoint(string name, int t, int(*action)(map<string, char>& check_events), chrono::system_clock::time_point target_check);

			int execute(map<string, char>& check_events) override;
		
			int count_until_next() override;
	};
}

#endif
