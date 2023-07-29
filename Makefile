# Callum Gran 2023
# See LICENSE for license info

OBJDIR = .obj
TESTDIR = tests
SRC = algorithms

DIRS := $(shell find $(SRC) $(TESTDIR) -type d)

SRCS := $(shell find $(SRC) -type f -name "*.c")
BENCHSRCS := $(shell find $(TESTDIR) -type f -name "*.c")

OBJS := $(SRCS:%.c=$(OBJDIR)/%.o)
BENCHOBJS := $(BENCHSRCS:%.c=$(OBJDIR)/%.o)

CFLAGS = -Iinclude -Wall -Wextra -Wshadow -std=c11 -lrt -lm -D_POSIX_C_SOURCE=200809L -O2

.PHONY: format clean tags bear $(OBJDIR)
TARGET_BUBBLESORT_TEST = bubblesort_test
TARGET_INSERTIONSORT_TEST = insertionsort_test
TARGET_QUICKSORT_TEST = quicksort_test
TARGET_QUICKSORT_BENCHMARK = quicksort_benchmark

clean:
	rm -rf $(OBJDIR) $(TARGET_BUBBLESORT_TEST) $(TARGET_INSERTIONSORT_TEST) $(TARGET_QUICKSORT_TEST) $(TARGET_QUICKSORT_BENCHMARK)

tags:
	@ctags -R

bear:
	@bear -- make

format:
	python format.py

bubblesort_test:
	$(CC) ./algorithms/bubblesort/gen_bubblesort.c ./tests/bubblesort_test.c $(CFLAGS) -o $(TARGET_BUBBLESORT_TEST)

insertionsort_test:
	$(CC) ./algorithms/insertionsort/gen_insertionsort.c ./tests/insertionsort_test.c $(CFLAGS) -o $(TARGET_INSERTIONSORT_TEST)

quicksort_test:
	$(CC) ./algorithms/quicksort/gen_quicksort.c ./tests/quicksort_test.c $(CFLAGS) -o $(TARGET_QUICKSORT_TEST)

quicksort_benchmark:
	$(CC) ./algorithms/quicksort/gen_quicksort.c ./tests/benchmark_qs.c ./tests/benchmark_commons.c $(CFLAGS) -o $(TARGET_QUICKSORT_BENCHMARK)

$(OBJDIR):
	$(foreach dir, $(DIRS), $(shell mkdir -p $(OBJDIR)/$(dir)))

$(OBJDIR)/%.o: ./%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/$(TESTDIR)/%.o: $(TESTDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@