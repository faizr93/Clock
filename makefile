CC = g++
CFLAGS = -Wall -g -I/c/msys64/ucrt64/include
LDFLAGS = -L/c/msys64/ucrt64/lib -lraylib -lglfw3 -lopengl32 -lgdi32 -luser32

# Set the filename dynamically
FILENAME = main
TARGET = $(FILENAME).exe
SRC = $(FILENAME).cpp time.cpp button.cpp text.cpp stopWatch.cpp

# Default target that handles clean, build, and run
all: clean $(TARGET) run

# Rule to create the executable
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

# Rule to clean the target executable
clean:
	if exist $(TARGET) del $(TARGET)

# Rule to run the program after compilation
run: $(TARGET)
	@echo Running $(TARGET)...
	@$(TARGET)

.PHONY: all clean run
