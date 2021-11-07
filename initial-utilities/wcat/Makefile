%: %.c
	cc -o $@ $< -Wall -Werror

.PHONY: all test clean
all: wcat
test: wcat
	./test-wcat.sh

clean:
	rm wcat
