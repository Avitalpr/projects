
INC_DIR = ../inc
SRC_DIR = ../src
INL_DIR = ../inc/inl

CXX = g++
CC = $(CXX)

WARNINGS = -pedantic
WARNINGS += -Wall -Werror

DEBUG = -g3
CXX_STD = c++17

CXXFLAGS = $(WARNINGS) $(DEBUG) -std=$(CXX_STD)

CPPFLAGS = -I$(INC_DIR)

LDLIBS = -lpthread
TARGET = utest
OBJS = utest.o  $(SRC_DIR)/temperature_sensor.o $(SRC_DIR)/smoke_sensor.o $(SRC_DIR)/sensor_manager.o

$(TARGET):$(OBJS)

$(SRC_DIR)/sensor_manager.o: $(INC_DIR)/sensor_manager.hpp $(INC_DIR)/sensor.hpp
$(SRC_DIR)/smoke_sensor.o: $(INC_DIR)/smoke_sensor.hpp $(INC_DIR)/sensor.hpp $(INC_DIR)/notify.hpp
$(SRC_DIR)/temperature_sensor.o: $(INC_DIR)/temperature_sensor.hpp $(INC_DIR)/sensor.hpp $(INC_DIR)/notify.hpp
utest.o: $(INC_DIR)/temperature_sensor.hpp $(INC_DIR)/smoke_sensor.hpp $(INC_DIR)/sensor_manager.hpp $(INC_DIR)/mu_test.h $(INC_DIR)/date_time.hpp $(INC_DIR)/location.hpp $(INC_DIR)/event.hpp

check: $(TARGET)
	./$(TARGET) -v
	
clean:
	@$(RM) $(TARGET) $(OBJS)
	
.PHONY: check clean
