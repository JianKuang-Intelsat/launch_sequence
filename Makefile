CPP=clang++ -std=c++17

# Build and run.
launch: launch_sequence.exe
	./launch_sequence.exe test_countdown.txt

# Clean outputs.
clean:
	rm -rf *.o *.exe

# Build tests.
launch_sequence.exe: launch_sequence.cc funcs.cc event.cc checkpoint.cc sequence.cc
	$(CPP) -O3 -o launch_sequence.exe launch_sequence.cc funcs.cc event.cc checkpoint.cc sequence.cc
