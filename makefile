CC = g++
CFLAGS = -Wall -g -I/c/msys64/ucrt64/include
LDFLAGS = -L/c/msys64/ucrt64/lib -lraylib -lglfw3 -lopengl32 -lgdi32 -luser32

# Set the filename dynamically
FILENAME = main
TARGET = $(FILENAME).exe
SRC = $(FILENAME).cpp time.cpp button.cpp text.cpp stopWatch.cpp alarm.cpp globalConst.cpp
OBJ = $(SRC:.cpp=.o)

# Default target that handles clean, build, and run
all: clean $(TARGET) run

# Rule to create the executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET) $(LDFLAGS)

# Rule to compile the source files into object files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean the target executable
clean:
	if exist $(TARGET) del $(TARGET)
	if exist $(OBJ) del $(OBJ)

# Rule to run the program after compilation
run: $(TARGET)
	@echo Running $(TARGET)...
	@./$(TARGET)

.PHONY: all clean run