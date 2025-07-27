CC = g++
# CFLAGS = -fsanitize=address,undefined -D _DEBUG -O0 -Wall -Wextra
CFLAGS = -D _DEBUG -O0 -Wall -Wextra


DEB_ASM:= 0

ifeq ($(DEB_ASM), 1)
	CFLAGS += -DPRINT_DEBUG
endif


SOURCES_DIR_ASSEMBLER=Sources
SOURCES_DIR_PARSER=../Parser/Sources

SOURCES = $(wildcard $(SOURCES_DIR_ASSEMBLER)/*.cpp) $(wildcard $(SOURCES_DIR_PARSER)/*.cpp)

OBJECTS = $(SOURCES:.cpp =.o)

EXECUTABLE = Assembler

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) -o $(EXECUTABLE)

%.o: %.cpp
	$(CC) -c $(SOURCES) $(CFLAGS) -I../Parser/Headers -IHeaders $< -o $@

clean:
	@rm -rf $(EXECUTABLE)









































# CC = g++
# CFLAGS = -fsanitize=address,undefined -D _DEBUG -O0 -Wall -Wextra

# BUILD_DIR = build

# SOURCES_DIR_ASSEMBLER=Sources
# SOURCES_DIR_PARSER=../Parser/Sources

# SOURCES = $(wildcard $(SOURCES_DIR_ASSEMBLER)/*.cpp) $(wildcard $(SOURCES_DIR_PARSER)/*.cpp)

# OBJECTS = $(BUILD_DIR)/asm_main.o $(BUILD_DIR)/asm_function.o $(BUILD_DIR)/pars_function.o

# EXECUTABLE = Assembler

# all: $(EXECUTABLE)

# $(EXECUTABLE): $(OBJECTS)
# 	$(CC) $(OBJECTS) $(CFLAGS) -o $(EXECUTABLE)

# $(BUILD_DIR)/%.o: $(SOURCES)
# 	@mkdir -p $(BUILD_DIR)
# 	$(CC) -c $(CFLAGS) -I../Parser/Headers -IHeaders $< -o $@

# clean:
# 	@rm -rf $(BUILD_DIR)








# CC = g++
# CFLAGS = -fsanitize=address,undefined -D _DEBUG -O0 -Wall -Wextra

# SOURCES_DIR_ASSEMBLER = Sources
# SOURCES_DIR_PARSER = ../Parser/Sources
# SOURCES = $(wildcard $(SOURCES_DIR_ASSEMBLER)/*.cpp ) $(wildcard $(SOURCES_DIR_PARSER)/*.cpp )

# OBJECTS = $(SOURCES:.cpp =.o)

# BUILD_DIR = build

# EXECUTABLE = Assembler

# $(EXECUTABLE): $(OBJECTS)
# 	$(CC) $(OBJECTS) -o $@

# $(OBJECTS): $(SOURCES)
# 	@mkdir -p $(BUILD_DIR)
# 	$(CC) $(CFLAGS) -I../Parser/Headers -IHeaders $^ -o $(BUILD_DIR)/asm_functions.o $(BUILD_DIR)/asm_main.o $(BUILD_DIR)/pars_functions.o



# clean: 
# 	rm -rf $(BUILD_DIR) $(EXECUTABLE)

