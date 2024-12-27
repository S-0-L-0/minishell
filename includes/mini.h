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

#define SYNERR "minishell: syntax error near unexpected token '|'\n"
#define QTERR "minishell: Unbalanced quotes in the string.\n"

enum type {
	COMMAND,    // di default 0
	FLAG,   // di default 1
	COMMAND_ARGUMENT,   // di default 2
	INPUT_REDIRECTION,   // di default 3
	OUTPUT_REDIRECTION,   // di default 4
	APPEND_REDIRECTION,   // di default 5
	
};

typedef struct s_cmd
{
	char			*word;
	enum type		type;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_fullcmd
{

	char				*line;
	struct s_fullcmd	*next;
	t_cmd				**cmd_head;
}	t_fullcmd;


typedef struct s_quotes
{
	int		in_single_quote;
	int		in_double_quote;
	char	*start;
	char	*end;
}	t_quotes;

typedef struct s_pipe
{
	int			fd[2];
	int			tmp_fd;
	int			std_in;
	int			std_out;
	pid_t		pid;

}	t_pipe;

// int			check_pipe(char *str);
// void		set_squotes (t_quotes *quotes, char *str);
// int			check_pipe(char *str);
// void		set_squotes(t_quotes *quotes, char *str);
// t_fullcmd	*split_string_to_list(char *str, t_fullcmd *head, t_quotes *quotes);
void		skip_spaces(t_quotes *quotes);
t_fullcmd	*split_string_to_list(char *str, t_fullcmd *head, t_quotes *quotes);
void		free_cmd_list(t_cmd *cmd);
void		free_all_lists(t_fullcmd *fullcmd);
t_fullcmd	*create_newnode(char *start, char *end);
void		handle_newnode(t_fullcmd **list_head, t_fullcmd **current, char *start, char *end);
int			handle_quotes(char c, int *in_single_quote, int *in_double_quote);
void		set_squotes(t_quotes *quotes, char *str);
void		add_cmd_node(t_cmd *new_cmd, t_cmd **cmd_head);
int			create_cmd_node(char *start, int len, t_cmd **cmd_head);
int			process_line(char *line, t_cmd **cmd_head);
void		print_cmd_list(t_cmd *cmd);
int			fill_cmd_lists(t_fullcmd *fullcmd);
int			is_inside_quotes(const char *str, int index);
int			check_dbpipe(const char *str);
int			check_pipe(const char *str);
int			pipe_checker(const char *str);
char		*find_path(char *cmd);
char		**make_command(t_cmd *cmd_list);
int			execute_command(char *path, char **cmd, char **envp);
int			execute_line(t_fullcmd *list, char **envp);
void		free_matrix(char **matrix);
char		**ft_split(char const *s, char c);
char		*ft_strjoin(char *s1, char *s2);
int			ft_strlen(const char *str);
char		*ft_strdup(const char *s1);
void		set_pipe(t_pipe *pipe);

#endif