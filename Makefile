all:
	clang -o stack-hack stack.c

safe:
	clang -fsanitize=safe-stack -o stack-hack stack.c
