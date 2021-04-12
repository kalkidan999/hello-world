#include "shell.h"
char *tok_buf = NULL;
int   tok_bufsize  = 0;
int   tok_bufindex = -1;
/* special token to indicate end of input  */
struct token_s eof_token = {
  0
};

void add_to_buf(char c)
{
    tok_buf[tok_bufindex++] = c;
    if(tok_bufindex >= tok_bufsize)
    {
        char *tmp = realloc(tok_buf, tok_bufsize*2);
        if(!tmp)
        {
            errno = ENOMEM;
            return;
        }
        tok_buf = tmp;
        tok_bufsize *= 2;
    }
}
struct token_s *create_token(char *str)
{
char *nstr;
struct token_s *tok;
tok = malloc(sizeof(struct token_s));
    
    if(!tok)
    {
        return NULL;
    }
    memset(tok, 0, sizeof(struct token_s));
    tok->text_len = _strlen(str);
    
    nstr = malloc(tok->text_len+1);
    
    if(!nstr)
    {
        free(tok);
        return NULL;
    }
    
    _strcpy(nstr, str);
    tok->text = nstr;
    
    return tok;
}
void free_token(struct token_s *tok)
{
    if(tok->text)
    {
        free(tok->text);
    }
    free(tok);
}
struct token_s *tokenize(struct source_s *src)
{
    int  endloop = 0;
struct token_s *tok;
char nc;
    if(!src || !src->buffer || !src->bufsize)
    {
        errno = ENODATA;
        return &eof_token;
    }
    
    if(!tok_buf)
    {
        tok_bufsize = 1024;
        tok_buf = malloc(tok_bufsize);
        if(!tok_buf)
        {
            errno = ENOMEM;
            return &eof_token;
        }
    }
    tok_bufindex     = 0;
    tok_buf[0]       = '\0';
    nc = next_char(src);
    if(nc == ERRCHAR || nc == EOF)
    {
        return &eof_token;
    }
    do
    {
        switch(nc)
        {
            case ' ':
            case '\t':
                if(tok_bufindex > 0)
                {
                    endloop = 1;
                }
                break;
                
            case '\n':
                if(tok_bufindex > 0)
                {
                    unget_char(src);
                }
                else
                {
                    add_to_buf(nc);
                }
                endloop = 1;
                break;
                
            default:
                add_to_buf(nc);
                break;
        }
        if(endloop)
        {
            break;
        }
    } while((nc = next_char(src)) != EOF);
    if(tok_bufindex == 0)
    {
        return &eof_token;
    }
    
    if(tok_bufindex >= tok_bufsize)
    {
        tok_bufindex--;
    }
    tok_buf[tok_bufindex] = '\0';
    tok = create_token(tok_buf);
    if(!tok)
    {
        fprintf(stderr, "error: failed to alloc buffer: %s\n",
                strerror(errno));
        return &eof_token;
    } 
    tok->src = src;
    return tok;
} 
