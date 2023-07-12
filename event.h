
#ifndef EVENT_H
#define EVENT_H

using namespace std;
// Function template for any function signature
template <typename... Args>
using FunctionPtr = int(*)(Args...);

namespace launch_funcs {
	
	class Event {

		public:

			string identifier;
			int t_minus;
			int seconds_until_next;
			int (*action)(map<string, char>& check_event);
			Event* next_event;
		
			Event(string name, int t, int (*action)(map<string, char>& check_event));

			virtual int execute(map<string, char>& check_events);
		
			virtual int count_until_next();
	};
}

#endif
