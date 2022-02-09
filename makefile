CC := gcc
CPP := g++
LDFLAGS :=
C_SOURCES := $(wildcard *.c)
C_EXECUTABLE := $(C_SOURCES:.c=)
CPP_SOURCES := $(wildcard *.cpp)
CPP_EXECUTABLE := $(CPP_SOURCES:.cpp=)
 
all:$(C_EXECUTABLE) $(CPP_EXECUTABLE)

$(C_EXECUTABLE):$(C_SOURCES)
		$(CC) $< $(LDFLAGS) $(CFLAGS) -o $@

$(CPP_EXECUTABLE):$(CPP_SOURCES)
		$(CPP) $< $(LDFLAGS) $(CFLAGS) -o $@

run:
	node ocma bot_A bot_B bot_C bot_D