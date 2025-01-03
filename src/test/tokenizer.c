#include "../../includes/mini.h"

void	add_cmd_node(t_cmd *new_cmd, t_cmd **cmd_head)
{
	t_cmd    *current;

	if (*cmd_head == NULL)
		*cmd_head = new_cmd;
	else
	{
		current = *cmd_head;
		while (current->next)
			current = current->next;
		current->next = new_cmd;
	}
}

static bool ck_mi_stai_sul_cazzo(char *str)
{
	while(str)
	{
		if (ft_isdigit(*str))
			str ++;
		else if (*str == '<' || *str == '>')
			return (false);
		else
			break ;
	}
	return (true);
}

int	create_cmd_node(char *start, int len, t_cmd **cmd_head)
{
	t_cmd   *new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (1);
	new_cmd->word = malloc(sizeof(char) * (len + 1));
	new_cmd->is_arg = true;
	if (!new_cmd->word)
	{
		free(new_cmd);
		return (1);
	}
	strncpy(new_cmd->word, start, len);
	new_cmd->word[len] = '\0';
	new_cmd->next = NULL;
	new_cmd->is_arg = ck_mi_stai_sul_cazzo(new_cmd->word);
	add_cmd_node(new_cmd, cmd_head);
	return (0);
}

int	process_line(char *line, t_cmd **cmd_head)
{
	t_quotes    quotes;
	int         continue_main;
	
	set_squotes(&quotes, line);
	continue_main = 1;
	while (*line && continue_main)
	{
		while (*line == ' ' && !quotes.in_single_quote && !quotes.in_double_quote)
			line++;
		if (*line)
		{
			quotes.start = line;
			while (*line && (*line != ' ' || quotes.in_single_quote || 
					quotes.in_double_quote))
			{
				handle_quotes(*line, &quotes.in_single_quote, &quotes.in_double_quote);
				line++;
			}
			quotes.end = line;
			if (create_cmd_node(quotes.start, quotes.end - quotes.start, cmd_head))
				return (1);
			if (*line)
				line++;
		}
		else
			continue_main = 0;
	}
	return (0);
}
