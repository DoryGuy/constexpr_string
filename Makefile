
CXX=g++-13
CXX_VERSION=c++23
OPTIMIZE_FLAG=-O3
DEBUG_FLAG=-g
WARNING_FLAGS=-Wall -Wextra -Wconversion
CXXFLAGS=-std=$(CXX_VERSION) $(OPTIMIZE_FLAG) $(WARNING_FLAGS) 
INCLUDE_DIR=/usr/local/include
LIB_DIR=/usr/local/lib
RM=rm


# Define a pattern rule that compiles every .cpp file into a .o file
%.o : %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

LIBRARIES= \
	-lfmt

# The build target 
TARGET = test_program
 
all: $(TARGET)
 
$(TARGET): constexpr_string.hpp main.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.o  -L$(LIB_DIR) $(LIBRARIES)

clean:
	$(RM) *.o $(TARGET)
