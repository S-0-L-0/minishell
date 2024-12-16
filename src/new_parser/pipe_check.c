#include "../../includes/mini.h"
#include <stdio.h>
#include <stdbool.h>

#define SYNERR "minishell: syntax error near unexpected token '|'\n"

bool is_inside_quotes(char *str, int index)
{
	bool in_single_quotes = false;
	bool in_double_quotes = false;
	int i = 0;

	while (i < index)
	{
		if (str[i] == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (str[i] == '"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		i++;
	}
	// Se siamo dentro una coppia di apici singoli o doppi, restituiamo true
	return (in_single_quotes || in_double_quotes);
}

//controllo sulla doppia pipe e uscita con errore
int check_dbpipe(char *str)
{
	int	i;

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

int check_pipe(char *str)
{
	int	i;
	bool flag;

	i = 0;
	flag = false;
	while (str[i] < 33)
		i++;
	if (str[i] == '|' && !is_inside_quotes(str, i))
		return (printf(SYNERR), 1);
	i++;
	while (str[i])
	{
		if (is_inside_quotes(str, i))
			i++;
		else if (str[i] > 32 && str[i] < 127 && str[i] != '|')
			flag = true;
		else if (str[i] == '|' && flag == true)
			flag = false;
		else if (str[i] == '|' && flag == false)
			return (printf(SYNERR), 1);
		i++;
	}
	if (flag == false)
		return (printf(SYNERR), 1);
	return (0);
}

int pipe_checker(char *str)
{
	if (check_pipe(str) == 1)
		return (1);
	if (check_dbpipe(str) == 1)
		return (1);
	return (0);
}