CC = gcc
OBJS = hash.c hash.h
CFLAGS = 
TEST_SOURCES := $(wildcard *_test.c)
TEST_OBJECTS := $(patsubst %.c,%.out,$(wildcard *_test.c))
TESTS := $(patsubst %.c,%o,$(wildcard *_test.c))
#lexer.c lexer.h token.c token.h eval.c eval.h parser.h parser.c tools.h tools.c
#
#MyPureLisp.out: main.c $(OBJS)
#	gcc main.c $(OBJS) \
#	-o MyPureLisp.out
#
#run: MyPureLisp.out
#	./MyPureLisp.out
#
.PHONY: test
test: $(TEST_OBJECTS)
	@for obj in $(TEST_OBJECTS); do \
		echo "about: $$obj ----------------------------------"; \
		./$$obj; \
	done

%_test.out: %_test.o %.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f *.o
	rm -f *.out

