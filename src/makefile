CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
LIBS = -lncurses

TARGET = library_system
SRCS = main.cpp Book.cpp Library.cpp User.cpp LibraryUI.cpp
OBJS = $(SRCS:.cpp=.cpp.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o  $@ $^ $(LIBS)

%.cpp.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean