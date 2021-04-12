#ifndef _SIMPLESHELL_
#define _SIMPLESHELL_
/* Libraries */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
/* Prototypes */

void my_handler(int var);
void print_prompt2(void);

char *read_cmd(void);
#endif
