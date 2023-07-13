
#ifndef EVENT_H
#define EVENT_H

#include <string>

using namespace std;
// Function template for any function signature

namespace launch_funcs {
	
	class Event {

		public:

			string identifier;
			string etype;
			int t_minus;
			int seconds_until_next;
			int (*action)(map<string, char>&);
			Event* next_event;
		
			Event(string name, int t);

			virtual int execute(map<string, char>&);
		
			virtual int count_until_next();
	};
}

#endif
