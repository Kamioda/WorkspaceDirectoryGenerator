CXX = g++
CXXFLAGS = -std=c++20 -I ./3rdparty/json/include
TARGET = wdg
SRCS = Main.cpp
OBJS = $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^
$(OBJS): $(SRCS)
	$(CXX) $(CXXFLAGS) -c $^
all: clean $(OBJS) $(TARGET)
clean:
	rm -f $(OBJS) $(TARGET)
