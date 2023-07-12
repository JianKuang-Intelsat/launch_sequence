#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include "sequence.h"
#include "funcs.h"

using namespace std;
using namespace launch_funcs;

int main(int argc, char** argv) {
	int year, month, day, hour, minute, second, millisecond;
	string e_type, name, line;
	int t_minus;
	ifstream file(argv[1]);
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
	if (!file.is_open()) {
		std::cout << "Failed to open file " << argv[1] << endl;
		return -1;
	}
	while (getline(file, line)) {
		istringstream iss(line);
		Event* event = NULL;
		Checkpoint* checkpoint = NULL;
		if (iss >> e_type >> name >> t_minus) {
			if(e_type == "E") {
				event = new Event(name, t_minus);
				falcon9 -> add_event(event);
			}
			else {
				checkpoint = new Checkpoint(name, t_minus, falcon9 -> target_launch);
				falcon9 -> add_event(checkpoint);
			}
		}
	}
//	Event* main_engine_start = new Event("main_engine_start", 3);
//	Event* engine_chill = new Event("engine_chill", 16);
//	Checkpoint* final_check = new Checkpoint("final_check", 10, falcon9 -> target_launch);
//	falcon9 -> add_event(main_engine_start);
//	falcon9 -> add_event(final_check);
//	falcon9 -> add_event(engine_chill);
	falcon9 -> start_countdown();
	auto now = std::chrono::system_clock::now();
	int error = std::chrono::duration_cast<std::chrono::milliseconds>(falcon9 -> target_launch - now).count();
	cout << error << " milliseconds off" << endl;
	return 0;
}
