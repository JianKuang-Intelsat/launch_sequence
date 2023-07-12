#include <iostream>
#include <thread>
#include <map>
#include "funcs.h"

using namespace std;
using namespace launch_funcs;

int launch_funcs::func_pre_start(map<string, char>& check_events) {
	return 0;
}

int launch_funcs::func_lift_off(map<string, char>& check_events) {
        cout << "Lift Off!" << endl;
        return STATUS_NOMINAL;
}

int launch_funcs::func_initial_check(map<string, char>& check_events) {
	if(check_events["weather"] != CHECK_GO or check_events["range"] != CHECK_GO) {
		check_events["initial_check"] = CHECK_NOGO;
		return CHECK_NOGO;
	}
        check_events["initial_check"] = CHECK_GO;
        return CHECK_GO;
}

int launch_funcs::func_mid_check(map<string, char>& check_events) {
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
		if(pair.second != STATUS_NOMINAL and pair.first != "main_engine_ignition") {
			check_events["final_check"] = CHECK_NOGO;
			return CHECK_NOGO;
		}
	}
	check_events["final_check"] = CHECK_GO;
	return CHECK_GO;
}

int launch_funcs::func_main_engine_ignition(map<string, char>& check_events) {
	cout << "Main Engine Ignition!" << endl;
	return STATUS_NOMINAL;
}

int launch_funcs::func_final_director(map<string, char>& check_events) {
	cout << "Launch director confirm go for launch" << endl;
	check_events["final_director"] = STATUS_NOMINAL;
        return STATUS_NOMINAL;
}

int launch_funcs::func_water_deluge_activate(map<string, char>& check_events) {
        cout << "Water deluge activated" << endl;
        check_events["water_deluge_activate"] = STATUS_NOMINAL;
        return STATUS_NOMINAL;
}

int launch_funcs::func_tanks_pressuring(map<string, char>& check_events) {
        cout << "Tanks pressuring start" << endl;
	this_thread::sleep_for(10s);                     // Assuming pressuring takes 10 seconds
	cout << "All tanks at flight pressure" << endl;
        check_events["tanks_pressuring"] = STATUS_NOMINAL;
        return STATUS_NOMINAL;
}

int launch_funcs::func_thrust_vector_actuator_test(map<string, char>& check_events) {
        cout << "Thrust vector actuator test started" << endl;
        this_thread::sleep_for(3s);                     // Assuming TVC test takes 3 seconds
        cout << "Thrust vector actuator test completed" << endl;
        check_events["thrust_vector_actuator_test"] = STATUS_NOMINAL;
        return STATUS_NOMINAL;
}

int launch_funcs::func_telemetry_check(map<string, char>& check_events) {
        cout << "Telemetry check started" << endl;
        this_thread::sleep_for(6s);                     // Assuming TVC test takes 3 seconds
        cout << "Telemetry check completed" << endl;
        check_events["telemetry_check"] = STATUS_NOMINAL;
        return STATUS_NOMINAL;
}

int launch_funcs::func_start_up(map<string, char>& check_events) {
        cout << "Flight Computer start up" << endl;
        check_events["start_up"] = STATUS_NOMINAL;
        return STATUS_NOMINAL;
}

int launch_funcs::func_fts_armed(map<string, char>& check_events) {
	cout << "FTS Armed" << endl;
	check_events["fts_armed"] = STATUS_NOMINAL;
        return STATUS_NOMINAL;
}

int launch_funcs::func_engine_chill(map<string, char>& check_events) {
        cout << "Engine Chill started" << endl;
        this_thread::sleep_for(5s);                     // Assuming engine chill takes 5 seconds
        cout << "Engine Chill completed" << endl;
        check_events["engine_chill"] = STATUS_NOMINAL;
        return STATUS_NOMINAL;
}

int launch_funcs::func_lox_loading(map<string, char>& check_events) {
	cout << "LOX loading started" << endl;
	this_thread::sleep_for(20s);                     // Assuming LOX loading takes 20 seconds
	cout << "LOX loading completed" << endl;
	check_events["lox_loading"] = STATUS_NOMINAL;
        return STATUS_NOMINAL;
}

int launch_funcs::func_fuel_loading(map<string, char>& check_events) {
        cout << "Fuel loading started" << endl;
        this_thread::sleep_for(20s);                     // Assuming fuel loading takes 20 seconds
        cout << "Fuel loading completed" << endl;
        check_events["fuel_loading"] = STATUS_NOMINAL;
        return STATUS_NOMINAL;
}

int launch_funcs::func_internal_power(map<string, char>& check_events) {
        cout << "Rocket on internal power" << endl;
	check_events["internal_power"] = STATUS_NOMINAL;
        return STATUS_NOMINAL;
}
