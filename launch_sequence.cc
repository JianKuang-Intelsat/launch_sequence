#include <iostream>
#include "sequence.h"
#include "funcs.h"

using namespace std;
using namespace launch_funcs;

int main() {
	int year, month, day, hour, minute, second, millisecond;
	cout << "Please enter target launch time in UTC" << endl;
	cout << "Year: ";
	cin >> year;
	cout << "Month: ";
	cin >> month;
	cout << "Day: ";
	cin >> day;
	cout << "Hour: ";
	cin >> hour;
	cout << "Minute: ";
	cin >> minute;
	cout << "Second: ";
	cin >> second;
	cout << "Millisecond: ";
	cin >> millisecond;
	Sequence* falcon9 = new Sequence(year, month, day, hour, minute, second, millisecond);
	Event* main_engine_start = new Event("main_engine_start", 3, func_main_engine_start);
	Event* engine_chill = new Event("engine_chill", 16, func_engine_chill);
	Checkpoint* mid_check = new Checkpoint("mid_check", 20, func_check, falcon9 -> target_launch);
	Checkpoint* final_check = new Checkpoint("final_check", 10, func_final_check, falcon9 -> target_launch);
	falcon9 -> add_event(main_engine_start);
	falcon9 -> add_event(final_check);
	falcon9 -> add_event(engine_chill);
	falcon9 -> add_event(mid_check);
	falcon9 -> start_countdown();
	auto now = std::chrono::system_clock::now();
	int error = std::chrono::duration_cast<std::chrono::milliseconds>(falcon9 -> target_launch - now).count();
	cout << error << " milliseconds off" << endl;
	return 0;
}
