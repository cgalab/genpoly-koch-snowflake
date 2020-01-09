make_koch_snowflake: make_koch_snowflake.c
	$(CC) -O2 -Wall -o "$@" $< -lm

clean:
	rm -f make_koch_snowflake

.PHONY: clean
