

CC = g++
# CFLAGS = -fsanitize=address,undefined -D _DEBUG -O0 -Wall -Wextra
CFLAGS = -D _DEBUG -O0 -Wall -Wextra


SOURCES_DIR_PROC = Sources
SOURCES_DIR_STACK = ../Stack/Sources

SOURCES_PROC = $(wildcard $(SOURCES_DIR_PROC)/*cpp ) 
SOURCES_STACK = $(wildcard $(SOURCES_DIR_STACK)/*cpp ) 


OBJECTS_PROC = $(SOURCES_PROC:.cpp =.o) 
OBJECTS_STACK = $(SOURCES_STACK:.cpp =.o) 

EXECUTABLE = Processor 


PRINT_STACK := 0
DEB_STACK   := 0
DEB_PROC    := 0


ifeq ($(PRINT_STACK), 1)
	CFLAGS += -DOTHER_PRINTS
endif

ifeq ($(DEB_STACK), 1)
	CFLAGS += -DUSE_DEBUG 
endif



ifeq ($(PROC_DEB=0), 1)
	CFLAGS += -DDEBUG 
endif

ifeq ($(PROC_STEP=0), 1)
	CFLAGS += -DSTEP
endif

ifeq ($(PROC_PRINT=0), 1)
	CFLAGS += -DRUN_PROC
endif


all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS_PROC) $(OBJECTS_STACK)
	$(CC) $(OBJECTS_PROC) $(OBJECTS_STACK) $(CFLAGS) -o $(EXECUTABLE)

%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

# $(OBJECTS_PROC): 


clean:
	@rm  -rf $(SOURCES_PROC/*.o)  $(SOURCES_STACK/*.o)  $(EXECUTABLE)
