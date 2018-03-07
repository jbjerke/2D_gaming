CXX = g++

# Warnings frequently signal eventual errors:
CXXFLAGS=-g -W -Wall -std=c++11 -Weffc++ -Wextra -pedantic -O0

OBJS = \
	p3.o
EXEC = run

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)

p3.o: p3.cpp

clean:
	rm -rf $(OBJS)
	rm -rf $(EXEC)
