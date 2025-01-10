#include "../../includes/mini.h"

void	free_cmd_list(t_cmd *cmd)
{
	t_cmd *current;

	current = cmd;
	while (current->next)
	{
		if (current->word)
			free(current->word);
		if (current)
			free(current);
		current = current->next;
	}
	free(current->word);
	free(current);
	return ;
}
void	free_all_lists(t_fullcmd *fullcmd)
{
	t_fullcmd	*current;

	current = fullcmd;
	while (current->next)
	{
		if (current->cmd_head)
		{
			free_cmd_list(*current->cmd_head);
			free(current->cmd_head);
		}
		free(current->line);
		free(current);
		current = current->next;
	}
	if (current->cmd_head)
		{
			free_cmd_list(*current->cmd_head);
			free(current->cmd_head);
		}
		free(current->line);
		free(current);
	return ;
}
