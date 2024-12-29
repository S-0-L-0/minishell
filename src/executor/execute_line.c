#include "../../includes/mini.h"

int	execute_command(char *path, char **cmd, char **envp)
{
	if (execve(path, cmd, envp) == -1)
		{
			printf("execve failed\n");
			return (1);
		}
	return(0);
}

int	execute_line(t_fullcmd *list, char **envp)
{
	t_fullcmd	*tmp;
	char		*path;
	char		**cmd;
	t_cmd		*cmd_head_tmp;
	t_pipe		ppoption;

	cmd_head_tmp = NULL;
	tmp = list;
	set_pipe(&ppoption);
	while (tmp)
	{
		cmd_head_tmp = *(tmp->cmd_head);
		if (check_red(tmp->line, '<'))
		{
			ppoption.tmp_fd = get_inputred_fd(cmd_head_tmp);
			dup2(ppoption.tmp_fd, 0);
		}
		if(tmp != list)
		{
			close(ppoption.fd[1]);
			ppoption.tmp_fd = dup(ppoption.fd[0]);
			close(ppoption.fd[0]);
			dup2(ppoption.tmp_fd, 0);
		}
		if (pipe(ppoption.fd) == -1)
		{
			perror("pipe");
			return (1);
		}
		ppoption.pid = fork();
		if (ppoption.pid == -1)
		{
			printf("fork failed\n");
			return (1);
		}
		if (ppoption.pid != 0)
		{
			if(tmp->next != NULL)
			{
				close(ppoption.fd[0]);
				dup2(ppoption.fd[1], 1);
			}
			path = find_path(cmd_head_tmp->word);
			cmd = make_command(cmd_head_tmp);
			execute_command(path, cmd, envp);
		}
		tmp = tmp->next;
	}
	while (waitpid(-1, NULL, 0) != -1)
	{
	}
	return (0);
}
