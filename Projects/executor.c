#include "shell.h"
#define MAX 400
#define max_args 255
char *search_path(char *file)
{
    char *PATH = getenv("PATH");
    char *p    = PATH;
    char *p2;
int plen;
    char path[MAX];
     struct stat st;
    while(p && *p)
    {
        p2 = p;
        while(*p2 && *p2 != ':')
        {
            p2++;
        }
        plen = p2-p;
        if(!plen)
        {
            plen = 1;
        }
	strncpy(path, p, p2-p);
        path[p2-p] = '\0';
	if(p2[-1] != '/')
        {
            _strcat(path, "/");
        }
        _strcat(path, file);
         if(stat(path, &st) == 0)
        {
            if(!S_ISREG(st.st_mode))
            {
                errno = ENOENT;
                p = p2;
                if(*p2 == ':')
                {
                    p++;
                }
                continue;
            }
            p = malloc(_strlen(path)+1);
            if(!p)
            {
                return NULL;
            }
            
	    _strcpy(p, path);
            return p;
        }
        else    /* file not found */
        {
            p = p2;
            if(*p2 == ':')
            {
                p++;
            }
        }
    }
    errno = ENOENT;
    return NULL;
}
int do_exec_cmd(int argc, char **argv)
{
	argc = argc;
    if(_strchr(argv[0], '/'))
    {
        execv(argv[0], argv);
    }
    else
    {
        char *path = search_path(argv[0]);
        if(!path)
        {
            return 0;
        }
        execv(path, argv);
        free(path);
    }
    return 0;
}
static inline void free_argv(int argc, char **argv)
{
    if(!argc)
    {
        return;
    }
    while(argc--)
    {
        free(argv[argc]);
    }
}
int do_simple_command(struct node_s *node)
{ 
    int argc = 0;
	struct node_s *child;
	char *argv[max_args+1];/* keep 1 for the terminating NULL arg */
    char *str;
	 
	 pid_t child_pid = 0;
	  int status = 0;
    if(!node)
    {
        return 0;
    }
	child = node->first_child;
    if(!child)
    {
        return 0;
    }
    while(child)
    {
        str = child->val.str;
        argv[argc] = malloc(_strlen(str)+1);
        
	if(!argv[argc])
        {
            free_argv(argc, argv);
            return 0;
        }
       
	_strcpy(argv[argc], str);
        if(++argc >= max_args)
        {
            break;
        }
        child = child->next_sibling;
    }
    argv[argc] = NULL;
    if((child_pid = fork()) == 0)
    {
        do_exec_cmd(argc, argv);
        fprintf(stderr, "error: failed to execute command: %s\n", 
                strerror(errno));
        if(errno == ENOEXEC)
        {
            exit(126);
        }
        else if(errno == ENOENT)
        {
            exit(127);
        }
        else
        {
            exit(EXIT_FAILURE);
        }
    }
    else if(child_pid < 0)
    {
        fprintf(stderr, "error: failed to fork command: %s\n", 
                strerror(errno));
        return 0;
    }
  
    waitpid(child_pid, &status, 0);
    free_argv(argc, argv);
    
    return 1;
}
/**
 * change_dir - Change Dirctorie
 * @cmd: Parsed Command
 * @er: Statue Last Command Excuted
 * Return: 0 Succes 1 Failed (For Old Pwd Always 0 Case No Old PWD)
 */
int change_dir(char **cmd, __attribute__((unused))int er)
{
	int value = -1;
	char cwd[MAX];

	if (cmd[1] == NULL)
		value = chdir(getenv("HOME"));
	else if (_strcmp(cmd[1], "-") == 0)
	{
		value = chdir(getenv("OLDPWD"));
	}
	else
		value = chdir(cmd[1]);

	if (value == -1)
	{
		perror("hsh");
		return (-1);
	}
	else if (value != -1)
	{
		getcwd(cwd, sizeof(cwd));
		setenv("OLDPWD", getenv("PWD"), 1);
		setenv("PWD", cwd, 1);
	}
	return (0);
}
