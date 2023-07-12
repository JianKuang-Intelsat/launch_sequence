#define STATUS_NOMINAL 0
#define NOT_RUN 1
#define MALFUNCTION -1
#define CHECK_GO 0
#define CHECK_NOGO -1

#ifndef FUNCS_H
#define FUNCS_H

#include <map>
#include <string>

using namespace std;

namespace launch_funcs {

	int func_pre_start(map<string, char>& check_events);

	int func_check(map<string, char>& check_events);

	int func_final_check(map<string, char>& check_events);
		
	int func_lift_off(map<string, char>& check_events);
	
	int func_main_engine_start(map<string, char>& check_events);
	
	int func_final_countdown(map<string, char>& check_events);
	
	int func_fts_armed(map<string, char>& check_events);
	
	int func_final_director(map<string, char>& check_events);
	
	int func_final_weather_check(map<string, char>& check_events);
	
	int func_telemetry_set_up(map<string, char>& check_events);
	
	int func_tanks_pressuring(map<string, char>& check_events);
	
	int func_internal_power(map<string, char>& check_events);
	
	int func_engine_chill(map<string, char>& check_events);
	
	int func_lox_loading(map<string, char>& check_events);
	
	int func_fuel_loading(map<string, char>& check_events);
	
	int func_start_up(map<string, char>& check_events);

	class FunctionMap {
		public:
			static FunctionMap& getInstance() {
				static FunctionMap instance;
				return instance;
			}
			std::map<std::string, int (*)(std::map<std::string, char>&)> func_map;

		private:
			FunctionMap() {
				func_map = {
					{"main_engine_start", func_main_engine_start},
					{"engine_chill", func_engine_chill},
					{"final_check", func_final_check},
					{"lift_off", func_lift_off},
					{"pre_start", func_pre_start},
					{"start_up", func_start_up},
					{"fuel_loading", func_fuel_loading},
					{"lox_loading", func_lox_loading},
					{"internal_power", func_internal_power},
					{"tanks_pressuring", func_tanks_pressuring},
					{"fts_armed", func_fts_armed}
				};
			}
	};
}

#endif
