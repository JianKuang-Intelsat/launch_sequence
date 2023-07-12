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

	std::map<char, string> check_status_display = {{0,"GO"},{1:"NO_GO"}};

	int func_void(map<string, char>& check_events);

	int func_check(map<string, char>& check_events);

	int func_final_check(map<string, char>& check_events);
		
	int func_lift_off(map<string, char>& check_events);
	
	int func_main_engine_start(map<string, char>& check_events);
	
	int func_sound_suppression_start(map<string, char>& check_events);
	
	int func_final_countdown(map<string, char>& check_events);
	
	int func_fts_armed(map<string, char>& check_events);
	
	int func_final_director(map<string, char>& check_events);
	
	int func_final_weather_check(map<string, char>& check_events);
	
	int func_telemetry_set_up(map<string, char>& check_events);
	
	int func_pressure_load(map<string, char>& check_events);
	
	int func_internal_power(map<string, char>& check_events);
	
	int func_engine_chill(map<string, char>& check_events);
	
	int func_lox_complete(map<string, char>& check_events);
	
	int func_fuel_complete(map<string, char>& check_events);
	
	int func_start_up(map<string, char>& check_events);

}

#endif
