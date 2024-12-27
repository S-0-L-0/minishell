#include "../../includes/mini.h"

char	*join_path(const char *dir, int dir_len, const char *cmd)
{
	char	*full_path;
	int		i;
	int		j;
	
	full_path = malloc(dir_len + strlen(cmd) + 2);
	if (!full_path)
		return (NULL);
	i = 0;
	while (i < dir_len)
	{
		full_path[i] = dir[i];
		i++;
	}
	full_path[i++] = '/';
	j = 0;
	while (cmd[j])
		full_path[i++] = cmd[j++];
	full_path[i] = '\0';
	return (full_path);
}

char	*find_command(char *cmd)
{
	char	*path;
	char	*full_path;
	int		i;
	int		start;
	
	if (!cmd || !*cmd)
		return (NULL);
	if (access(cmd, X_OK) == 0)
		return (strdup(cmd));
	path = getenv("PATH");
	if (!path)
		return (NULL);
	i = 0;
	start = 0;
	while (path[i])
	{
		if (path[i] == ':' || path[i + 1] == '\0')
		{
			if (path[i + 1] == '\0')
				i++;
			full_path = join_path(&path[start], i - start, cmd);
			if (!full_path)
				return (NULL);
			if (access(full_path, X_OK) == 0)
				return (full_path);
			free(full_path);
			start = i + 1;
		}
		i++;
	}
	return (NULL);
}

char	**create_argv(t_cmd *cmd_list)
{
	t_cmd	*current;
	char	**argv;
	int		i;
	int		cmd_count;
	
	cmd_count = 0;
	current = cmd_list;
	while (current)
	{
		cmd_count++;
		current = current->next;
	}
	
	argv = malloc(sizeof(char *) * (cmd_count + 1));
	if (!argv)
		return (NULL);
	
	i = 0;
	current = cmd_list;
	while (current)
	{
		argv[i] = strdup(current->word);
		if (!argv[i])
		{
			while (--i >= 0)
				free(argv[i]);
			free(argv);
			return (NULL);
		}
		i++;
		current = current->next;
	}
	argv[i] = NULL;
	
	return (argv);
}

int	execute_command(t_cmd *cmd_list)
{
	char	*cmd_path;
	char	**argv;
	pid_t	pid;
	int		status;
	
	if (!cmd_list || !cmd_list->word)
		return (1);
	cmd_path = find_command(cmd_list->word);
	if (!cmd_path)
	{
		write(2, "minishell: command not found: ", 29);
		write(2, cmd_list->word, strlen(cmd_list->word));
		write(2, "\n", 1);
		return (127);
	}
	argv = create_argv(cmd_list);
	if (!argv)
	{
		free(cmd_path);
		return (1);
	}
	pid = fork();
	if (pid == -1)
	{
		free(cmd_path);
		free(argv);
		return (1);
	}
	if (pid == 0)
	{
		if (execve(cmd_path, argv, environ//zz) == -1)
		{
			perror("minishell");
			exit(126);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		free(cmd_path);
		while (*argv)
			free(*argv++);
		free(argv - (status ? status : 1));
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			return (128 + WTERMSIG(status));
	}
	return (1);
}

int execute_command(t_fullcmd *list)
{
	t_fullcmd	*current;
	int			i;

	current = list;
	i = 0;
	while (current->next)
	{
		while (current->cmd_head[i]->next)
		{

			current->cmd_head[i] = current->cmd_head[i]->next;
		}
		current = current->next;
		i ++;
	}
	return (0);
}