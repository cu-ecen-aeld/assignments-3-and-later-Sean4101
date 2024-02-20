ifeq ($(CROSS_COMPILE),)
    CC := gcc  # Default compiler is gcc
else
    CC := $(CROSS_COMPILE)gcc
endif

all: writer

clean:
	rm -f writer *.o

writer: writer.c
	$(CC) -o writer writer.c