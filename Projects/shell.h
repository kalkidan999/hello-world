#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/wait.h>
/* prototype for scanning input*/
#define ERRCHAR         ( 0)
#define INIT_SRC_POS    (-2)
struct source_s
{   
char *buffer;       /* the input text */
long bufsize;       /* size of the input text */
long  curpos;       /* absolute char position in source */
};
char next_char(struct source_s *src);
void unget_char(struct source_s *src);
char peek_char(struct source_s *src);
void skip_white_spaces(struct source_s *src);
/* prototype for scanning tokens*/
struct token_s
{
 struct source_s *src;       /* source of input */
 int    text_len;            /* length of token text */
 char   *text;               /* token text */
};
/* the special EOF token, which indicates the end of input */
extern struct token_s eof_token;
struct token_s *tokenize(struct source_s *src);
void free_token(struct token_s *tok);
struct node_s *parse_simple_command(struct token_s *tok);
/* prototype for node header*/
enum node_type_e
{
    NODE_COMMAND,           /* simple command */
    NODE_VAR               /* variable name (or simply, a word) */
};
enum val_type_e
{
    VAL_SINT = 1,       /* signed int */
    VAL_UINT,         /* unsigned int */
    VAL_SLLONG,         /* signed long long */
    VAL_ULLONG,        /* unsigned long long */
    VAL_FLOAT,        /* floating point */
    VAL_LDOUBLE,        /* long double */
    VAL_CHR,          /* char */
    VAL_STR          /* str (char pointer) */
};
union symval_u
{
    long               sint;
    unsigned long      uint;
    long long          sllong;
    unsigned long long ullong;
    double             sfloat;
    long double        ldouble;
    char               chr;
    char              *str;
};
struct node_s
{
    enum   node_type_e type;    /* type of this node */
    enum   val_type_e val_type; /* type of this node's val field */
    union  symval_u val;        /* value of this node */
    int    children;            /* number of child nodes */
    struct node_s *first_child; /* first child node */
    struct node_s *next_sibling, *prev_sibling;
 /*
 * if this is a child node, keep
* pointers to prev/next siblings
 */
};
struct  node_s *new_node(enum node_type_e type);
void    add_child_node(struct node_s *parent, struct node_s *child);
void    free_node_tree(struct node_s *node);
void    set_node_val_str(struct node_s *node, char *val);
/* prototype for executor*/
char *search_path(char *file);
int do_exec_cmd(int argc, char **argv);
int do_simple_command(struct node_s *node);
/* prototype for prompt and read*/
void print_prompt1(void);
void print_prompt2(void);
char *read_cmd(void);
int  parse_and_execute(struct source_s *src);
/* prototype for string exec*/
int _strcmp(char *s1, char *s2);
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
char *_strtok(char *str, char *limi);
char *_strchr(char *stri, char car);
unsigned int _strcspn(char *str, char *pre);
#endif 
