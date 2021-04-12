#include <stdio.h>
#include "shell.h"
void my_handler(int var)
{
	(void) var;
	write(STDOUT_FILENO, "\n$ ", 3);
	fflush(stdout);
}
void print_prompt2(void)
{
    fprintf(stderr, "> ");
}
