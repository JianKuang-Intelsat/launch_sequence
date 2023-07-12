#include <iostream>
#include <thread>
#include <map>
#include "funcs.h"

using namespace std;
using namespace launch_funcs;

int launch_funcs::func_pre_start(map<string, char>& check_events) {
	return 0;
}

int launch_funcs::func_check(map<string, char>& check_events) {
	for(const auto &pair : check_events) {
		if(pair.second == MALFUNCTION) {
			check_events["mid_check"] = CHECK_NOGO;
			return CHECK_NOGO;
		}
	}
	check_events["mid_check"] = CHECK_GO;
	return CHECK_GO;
}

int launch_funcs::func_final_check(map<string, char>& check_events) {
	for(const auto &pair : check_events) {
		if(pair.first == "final_check") continue;
		if(pair.second != STATUS_NOMINAL and pair.first != "main_engine_start") {
			check_events["final_check"] = CHECK_NOGO;
			return CHECK_NOGO;
		}
	}
	check_events["final_check"] = CHECK_GO;
	return CHECK_GO;
}

int launch_funcs::func_lift_off(map<string, char>& check_events) {
	cout << "Lift Off!" << endl;
	return STATUS_NOMINAL;
}

int launch_funcs::func_main_engine_start(map<string, char>& check_events) {
	cout << "Main Engine Start!" << endl;
	return STATUS_NOMINAL;
}

int launch_funcs::func_final_countdown(map<string, char>& check_events) {
	cout << "Final countdown" << endl;
	check_events["final_countdown"] = STATUS_NOMINAL;
        return STATUS_NOMINAL;
}

int launch_funcs::func_fts_armed(map<string, char>& check_events) {
	cout << "FTS Armed" << endl;
        return STATUS_NOMINAL;
}

int launch_funcs::func_final_director(map<string, char>& check_events) {
	cout << "Launch director confirm launch proceed" << endl;
        return STATUS_NOMINAL;
}

int launch_funcs::func_final_weather_check(map<string, char>& check_events) {
	cout << "Final weather check" << endl;
        return STATUS_NOMINAL;
}

int launch_funcs::func_telemetry_set_up(map<string, char>& check_events) {
	cout << "Telemetry set up!" << endl;
        return STATUS_NOMINAL;
}

int launch_funcs::func_tanks_pressuring(map<string, char>& check_events) {
	cout << "Fuel and LOX pressuring start" << endl;
        return STATUS_NOMINAL;
}

int launch_funcs::func_internal_power(map<string, char>& check_events) {
	cout << "Rocket on internal power" << endl;
        return STATUS_NOMINAL;
}

int launch_funcs::func_engine_chill(map<string, char>& check_events) {
	cout << "Engine Chill" << endl;
	this_thread::sleep_for(5s);			// Assuming engine chill takes 5 seconds
	check_events["engine_chill"] = STATUS_NOMINAL;
	return STATUS_NOMINAL;
}

int launch_funcs::func_lox_loading(map<string, char>& check_events) {
	cout << "LOX load start" << endl;
        return STATUS_NOMINAL;
}

int launch_funcs::func_fuel_loading(map<string, char>& check_events) {
	cout << "Fuel load start" << endl;
        return STATUS_NOMINAL;
}

int launch_funcs::func_start_up(map<string, char>& check_events) {
	cout << "Rocket Start up" << endl;
	return STATUS_NOMINAL;
}
