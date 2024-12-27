#include "../../includes/mini.h"

int	is_inside_quotes(const char *str, int index)
{
	int in_single_quotes;
	int in_double_quotes;
	int i;

	in_single_quotes = 0;
	in_double_quotes = 0;
	i = 0;
	while (i < index)
	{
		if (str[i] == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (str[i] == '"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		i++;
	}
	return (in_single_quotes || in_double_quotes);
}

int	check_dbpipe(const char *str)
{
	int i;

	i = 0;
	while (str[i + 1])
	{
		if (str[i] == '|' && str[i + 1] == '|' && !is_inside_quotes(str, i))
		{
			printf("minishell: syntax error near unexpected token '||'\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_pipe(const char *str)
{
	int i;
	int flag;

	i = 0;
	flag = 0;
	while (str[i] && str[i] < 33)
		i++;
	if (str[i] == '|' && !is_inside_quotes(str, i))
		return (printf(SYNERR), 1);
	i++;
	while (str[i])
	{
		if (is_inside_quotes(str, i))
			i++;
		else if (str[i] > 32 && str[i] < 127 && str[i] != '|')
			flag = 1;
		else if (str[i] == '|' && flag == 1)
			flag = 0;
		else if (str[i] == '|' && flag == 0)
			return (printf(SYNERR), 1);
		i++;
	}
	if (flag == 0)
		return (printf(SYNERR), 1);
	return (0);
}

int	pipe_checker(const char *str)
{
	if (check_pipe(str))
		return (1);
	if (check_dbpipe(str))
		return (1);
	return (0);
}
