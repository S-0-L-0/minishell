#ifndef MINI_H
# define MINI_H

#include <readline/readline.h>      // readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history
#include <stdio.h>                  // printf, perror
#include <stdlib.h>                 // malloc, free, exit
#include <unistd.h>                 // write, access, open, read, close, fork, getcwd, chdir, unlink, dup, dup2, isatty, ttyname, ttyslot, pipe
#include <fcntl.h>                  // open
#include <sys/wait.h>               // wait, waitpid, wait3, wait4
#include <signal.h>                 // signal, sigaction, sigemptyset, sigaddset, kill
#include <sys/stat.h>               // stat, lstat, fstat
#include <dirent.h>                 // opendir, readdir, closedir
#include <string.h>                 // strerror
#include <termios.h>                // tcsetattr, tcgetattr
#include <sys/ioctl.h>              // ioctl
#include <term.h>                   // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
#include <stdlib.h>                 // getenv
#include <stdbool.h>

enum type {
	CMD,    // di default 0
	FLAG,   // di default 1
	PIPE, // di default 2
	ARG,   // di default 3
	RED,   // di default 4
};

typedef struct s_fullcmd
{
	char			*line;
	struct s_list	*next;
}	t_fullcmd;

typedef struct s_cmd
{
	char			*word;
	enum type		type;
	struct s_list	*next;
}	t_cmd;

typedef struct s_quotes
{
	bool	in_single_quote;
	bool	in_double_quote;
}	t_quotes;

int check_pipe(char *str);

#endif