CXX 		:= g++
CXXFLAGS 	:= -pedantic-errors -Wall -Wextra -O0 -std=c++11
LDFLAGS		:= -L/usr/lib -lstdc++ -lm -pthread
BUILD		:= ./build
OBJ_DIR		:= ./build/objects
APP_DIR		:= ./build/apps
TARGET1		:= client
TARGET2		:= server
INCLUDE		:= -Iinclude/
SRC			:= $(wildcard *.cpp)
OBJECTS		:= $(SRC:%.cpp=$(OBJ_DIR)/%.o)

all:
	make -j $(APP_DIR)/$(TARGET1) $(APP_DIR)/$(TARGET2)
$(OBJ_DIR)/%.o : %.cpp
	@mkdir -p $(@D)
	$(CXX) -c $(CXXFLAGS) $(INCLUDE) $< -o $@ $(LDFLAGS)

$(APP_DIR)/$(TARGET1) : $(OBJ_DIR)/client.o $(OBJ_DIR)/sockclient.o $(OBJ_DIR)/socket.o
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $^ -o $(APP_DIR)/$(TARGET1) $(LDFLAGS)

$(APP_DIR)/$(TARGET2) : $(OBJ_DIR)/server.o $(OBJ_DIR)/sockserver.o $(OBJ_DIR)/socket.o
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $(APP_DIR)/$(TARGET2) $^ $(LDFLAGS)
	
.PHONY: all clean build

clean:
	rm -rf $(OBJ_DIR)/*
	rm -rf $(APP_DIR)/*
