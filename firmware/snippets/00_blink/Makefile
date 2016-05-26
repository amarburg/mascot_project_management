OBJECTS=blink.o

GCC_DIR = /Users/aaron/ti/gcc
SUPPORT_FILE_DIRECTORY = ${GCC_DIR}/include

DEVICE  = msp430fr2311
CC      = $(GCC_DIR)/bin/msp430-elf-gcc
GDB     = $(GCC_DIR)/bin/msp430-elf-gdb

CFLAGS = -I $(SUPPORT_FILE_DIRECTORY) -mmcu=$(DEVICE) -O2 -g
LFLAGS = -L $(SUPPORT_FILE_DIRECTORY)

all: ${OBJECTS}
	$(CC) $(CFLAGS) $(LFLAGS) $? -o $(DEVICE).out

debug: all
	$(GDB) $(DEVICE).out
