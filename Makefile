all:
	clang -Wall -Werror -lpthread -o deadlock deadlock.c
	clang -Wall -Werror -lpthread -o check deadlock-check.c
	clang -Wall -Werror -lpthread -o timeout deadlock-timeout.c

clean:
	rm -f deadlock check timeout
