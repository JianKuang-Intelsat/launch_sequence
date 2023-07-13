#define STATUS_NOMINAL 0
#define NOT_RUN 1
#define MALFUNCTION -1
#define CHECK_GO 0
#define CHECK_NOGO -1
#define RANDOM_FAIL 5

#define BOLD    "\u001b[1m"
#define GRAY    "\u001b[38;5;248m"
#define CYAN    "\u001b[36m"
#define RED     "\u001b[31m"
#define GREEN   "\u001b[32m"
#define YELLOW  "\u001b[33m"
#define RESET   "\u001b[0m"

#ifndef FUNCS_H
#define FUNCS_H

#include <map>
#include <string>

using namespace std;

namespace launch_funcs {

	int func_pre_start(map<string, char>& check_events);
	int func_lift_off(map<string, char>& check_events);

	int func_initial_check(map<string, char>& check_events);	//check if weather and range are good to go
	int func_mid_check(map<string, char>& check_events);		//check if any malfunctions in actions
	int func_final_check(map<string, char>& check_events);		//check if everything is good to go
	
	int func_main_engine_ignition(map<string, char>& check_events);
	int func_final_director(map<string, char>& check_events);
	int func_water_deluge_activate(map<string, char>& check_events);
	int func_tanks_pressuring(map<string, char>& check_events);
	int func_thrust_vector_actuator_test(map<string, char>& check_events);
	int func_telemetry_check(map<string, char>& check_events);
	int func_start_up(map<string, char>& check_events);
	int func_fts_armed(map<string, char>& check_events);
	int func_engine_chill(map<string, char>& check_events);
	int func_lox_loading(map<string, char>& check_events);
	int func_fuel_loading(map<string, char>& check_events);
	int func_internal_power(map<string, char>& check_events);
	
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
					{"pre_start", func_pre_start},
					{"lift_off", func_lift_off},
					{"initial_check", func_initial_check},
					{"mid_check", func_mid_check},
					{"final_check", func_final_check},
					{"main_engine_ignition", func_main_engine_ignition},
					{"final_director", func_final_director},
					{"water_deluge_activate", func_water_deluge_activate},
					{"tanks_pressuring", func_tanks_pressuring},
					{"thrust_vector_actuator_test", func_thrust_vector_actuator_test},
					{"telemetry_check", func_telemetry_check},
					{"start_up", func_start_up},
					{"fts_armed", func_fts_armed},
					{"engine_chill", func_engine_chill},
					{"lox_loading", func_lox_loading},	
					{"fuel_loading", func_fuel_loading},
					{"lox_loading", func_lox_loading},
					{"internal_power", func_internal_power},
				};
			}
	};
}

#endif
