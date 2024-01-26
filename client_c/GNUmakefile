# Compiler Options
CC := clang
CFLAGS := -O3 -g # -fsanitize=address # Weird runtime infinite loop when using ASan

# Files
SRCS = $(wildcard *.c)
OBJS := $(SRCS:.c=.o)
EXECS := $(SRCS:.c=)

# Processes
all: $(EXECS)

$(EXECS): %: %.o
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean
clean:
	@rm -f $(OBJS) $(EXECS)
