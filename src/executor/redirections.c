#include "../../includes/mini.h"

int	check_red(char *str, char red_sign)
{
	int i;
	bool s_quote;
	bool d_quote;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	while(str[i])
	{
		if (str[i] == '\'' && !d_quote && !s_quote)
			s_quote = 1;
		else if (str[i] == '\'' && !d_quote && s_quote)
			s_quote = 0;
		else if (str[i] == '"' && !s_quote && !d_quote)
			d_quote = 1;
		else if (str[i] == '"' && !s_quote && d_quote)
			d_quote = 0;
		else if (str[i] == red_sign && !s_quote && !d_quote)
		{
			return(1);
		}
		i++;
	}
	return(0);
}

int	get_red_fd(t_cmd *cmd, char red_sign)
{
	int		i;
	int		s_quote;
	int		d_quote;
	t_cmd	*tmp;
	// int		pipefd[2];
	// pid_t	pid;
	// char	*prompt;
	

	s_quote = 0;
	d_quote = 0;
	tmp = cmd;
	while (tmp)
	{
		i = 0;
		while(tmp->word[i])
		{
			if (tmp->word[i] == '\'' && !d_quote && !s_quote)
				s_quote = 1;
			else if (tmp->word[i] == '\'' && !d_quote && s_quote)
				s_quote = 0;
			else if (tmp->word[i] == '"' && !s_quote && !d_quote)
				d_quote = 1;
			else if (tmp->word[i] == '"' && !s_quote && d_quote)
				d_quote = 0;
			else if (tmp->word[i] == red_sign && !s_quote && !d_quote)
			{
				i = 0;
				while (ft_isdigit(tmp->word[i]))
					i++;
				tmp->word = tmp->word + i;
				if (!ft_strncmp(tmp->word, "<", ft_strlen(tmp->word)))
				{
					if (access(tmp->next->word, F_OK) == -1)
					{
					printf("Error: file not found\n");
					return (1);
					}
					return(open(tmp->next->word, O_RDONLY | O_TRUNC, 0644));
				}
				else if (!ft_strncmp(tmp->word, ">", ft_strlen(tmp->word)))
				{
					return(open(tmp->next->word, O_CREAT | O_WRONLY | O_TRUNC, 0644));
				}
				else if (!ft_strncmp(tmp->word, "<<", ft_strlen(tmp->word)))
				{
					// if (pipe(pipefd) == -1)
					// {
					// 	printf("Error: pipe failed\n");
					// 	return (1);
					// }
					// pid = fork();
					// if (pid == -1)
					// {
					// 	printf("fork failed\n");
					// 	return (1);
					// }
					// if (pid != 0)
					// {
					// 	close(pipefd[1]);
					// 	prompt = NULL;
					// 	while (ft_strcmp(prompt, tmp->next->word) != 0)
					// 	{
					// 		prompt = readline(">");
					// 		write (pipefd[0], prompt, ft_strlen(prompt));
					// 	}
					// 	close(pipefd[0]);
					// }
					// else
					// {
					// 	close(pipefd[0]);
					// 	waitpid(pid, NULL, 0);
					// 	return(pipefd[1]);
					// }
					printf("Here doc not implemented yet\n");
				}
				else if (!ft_strncmp(tmp->word, ">>", ft_strlen(tmp->word)))
				{
					return(open(tmp->next->word, O_CREAT | O_WRONLY | O_APPEND, 0644));
				}
			}
			i++;
		}
		tmp = tmp->next;
	}
	return(0);
}
