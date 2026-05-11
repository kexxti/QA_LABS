CC=gcc
CFLAGS =-Wall -Werror -Wextra -std=c11 -D_POSIX_C_SOURCE=200809L
GCOV_FLAGS=--coverage

LDLIBS=-lcheck

OS = $(shell uname -s)
ifeq ($(OS),Linux)
	LDLIBS := $(LDLIBS) -lm -lsubunit
endif

SRC_FILES=$(wildcard ./string/s21*.c)
OBJ_FILES=$(patsubst %.c,%.o, $(SRC_FILES))

TARGET=s21_string
TEST_TARGET=$(TARGET)_test

LOGS_F=reports
HTML_F=html

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(TARGET).a

$(TARGET).a: $(OBJ_FILES)
	ar rc $@ $^
	ranlib $@ # in case ar doesn't have s flag

test: tests/*.c $(TARGET).a
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

gcov_report: tests/*.c $(SRC_FILES)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $^ -o $(LOGS_F)/$(TEST_TARGET) $(LDLIBS)
	./$(LOGS_F)/$(TEST_TARGET)
	lcov -t "Test" -d $(LOGS_F) -c -o $(LOGS_F)/$(TEST_TARGET).info
	genhtml $(LOGS_F)/$(TEST_TARGET).info -o $(HTML_F)

test_leaks: tests/*.c s21_string.a
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $^ -o $(LOGS_F)/$@ $(LDLIBS)

ifeq ($(OS),Darwin)
	leaks -atExit -- ./$(LOGS_F)/$@ > $(LOGS_F)/leaks.log
	grep -n "LEAK:" $(LOGS_F)/leaks.log ||:
else ifeq ($(OS),Linux)
	valgrind --leak-check=full --log-file=$(LOGS_F)/valgrind.log ./$(LOGS_F)/$@
	grep -n "ERROR SUMMARY:" $(LOGS_F)/valgrind.log | grep -v "0 errors" ||:
endif

clean:
	rm -f $(OBJ_FILES)
	rm -f $(TARGET).a
	rm -f test
	rm -rf $(HTML_F)/*
	rm -rf $(LOGS_F)/*

rebuild: clean all