CXX = g++
CC = $(CXX)
WARNINGS = -pedantic
WARNINGS += -Wall -Werror
DEBUG = -g3
CXX_STD = c++17
CXXFLAGS = $(WARNINGS) $(DEBUG) -std=$(CXX_STD)
CPPFLAGS = -I$(INC_DIR)

INC_DIR = ../inc
SRC_DIR = ../src

# $(SRC_DIR)/controller.o: CFLAGS += -fPIC
# $(SRC_DIR)/controller.o: controller.cpp

# $(SRC_DIR)/controller.o: CFLAGS += -fPIC
# $(SRC_DIR)/smoke_controller.o: smoke_controller.cpp

LDLIBS = -L /home/ -lpthread -rdynamic  -ldl -W -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system

TARGET = utest

OBJS = utest.o $(SRC_DIR)/temperature_controller.o $(SRC_DIR)/smoke_controller.o $(SRC_DIR)/router.o $(SRC_DIR)/server.o $(SRC_DIR)/server_manager.o $(SRC_DIR)/interest.o $(SRC_DIR)/config_data.o $(SRC_DIR)/reader.o $(SRC_DIR)/parser.o $(SRC_DIR)/create_controller.o $(SRC_DIR)/loader.o $(SRC_DIR)/logger.o $(SRC_DIR)/device.o $(SRC_DIR)/smart_home_ui.o

utest.o: $(INC_DIR)/mu_test.h $(INC_DIR)/controller.hpp $(INC_DIR)/temperature_controller.hpp $(INC_DIR)/smoke_controller.hpp $(INC_DIR)/observer.hpp $(INC_DIR)/router.hpp $(INC_DIR)/subject.hpp $(INC_DIR)/server.hpp $(INC_DIR)/server_manager.hpp $(INC_DIR)/interest.hpp $(INC_DIR)/config_data.hpp $(INC_DIR)/reader.hpp $(INC_DIR)/parser.hpp $(INC_DIR)/create_controller.hpp $(INC_DIR)/loader.hpp $(INC_DIR)/logger.hpp

$(SRC_DIR)/temperature_controller.o: $(INC_DIR)/temperature_controller.hpp $(INC_DIR)/controller.hpp $(INC_DIR)/observer.hpp $(INC_DIR)/config_data.hpp

$(SRC_DIR)/smoke_controller.o: $(INC_DIR)/controller.hpp $(INC_DIR)/config_data.hpp

$(SRC_DIR)/router.o: $(INC_DIR)/router.hpp $(INC_DIR)/subject.hpp $(INC_DIR)/observer.hpp $(INC_DIR)/interest.hpp

$(SRC_DIR)/server.o: $(INC_DIR)/server.hpp

$(SRC_DIR)/server_manager.o: $(INC_DIR)/server_manager.hpp $(INC_DIR)/router.hpp $(INC_DIR)/subject.hpp $(INC_DIR)/protocol.hpp $(INC_DIR)/event.hpp $(INC_DIR)/controller.hpp $(INC_DIR)/logger.hpp $(INC_DIR)/blocking_queue.hpp

$(SRC_DIR)/interest.o: $(INC_DIR)/interest.hpp

$(SRC_DIR)/config_data.o: $(INC_DIR)/config_data.hpp

$(SRC_DIR)/reader.o: $(INC_DIR)/reader.hpp $(INC_DIR)/parser.hpp $(INC_DIR)/config_data.hpp

$(SRC_DIR)/parser.o: $(INC_DIR)/parser.hpp

$(SRC_DIR)/create_controller.o: $(INC_DIR)/create_controller.hpp $(INC_DIR)/controller.hpp $(INC_DIR)/config_data.hpp

$(SRC_DIR)/loader.o: $(INC_DIR)/loader.hpp $(INC_DIR)/reader.hpp $(INC_DIR)/config_data.hpp $(INC_DIR)/controller.hpp $(INC_DIR)/router.hpp

$(SRC_DIR)/logger.o: $(INC_DIR)/logger.hpp

$(SRC_DIR)/parser.o: $(INC_DIR)/parser.hpp

$(SRC_DIR)/smart_home_ui.o: $(INC_DIR)/smart_home_ui.hpp $(INC_DIR)/device.hpp

$(SRC_DIR)/device.o: $(INC_DIR)/device.hpp

$(TARGET): $(OBJS)

check: $(TARGET)
	./$(TARGET) -v

vala: $(TARGET)
	valgrind --log-file=V1.log ./$(TARGET)
	valgrind --log-file=V2.log --leak-check=full --track-origins=yes ./$(TARGET

prod: CXXFLAGS += -O2 -DNDEBUG
prod: $(TARGET)
	./$(TARGET) -v

clean:
	@$(RM) $(TARGET) $(OBJS)

.PHONY: clean check
