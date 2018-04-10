CXX = g++

cube:change.cpp object.cpp
	$(CXX) change.cpp object.cpp -o cube -lglut -lGL

test:change.cpp my_trail.cpp
	g++ -o my_trail my_trail.cpp

clean:
	rm -f cube
