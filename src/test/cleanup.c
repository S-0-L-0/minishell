#include "../../includes/mini.h"

void	free_cmd_list(t_cmd *cmd)
{
	t_cmd *current;
	t_cmd *next;

	current = cmd;
	while (current)
	{
		next = current->next;
		free(current->word);
		free(current);
		current = next;
	}
}
void	free_all_lists(t_fullcmd *fullcmd)
{
	t_fullcmd *current;
	t_fullcmd *next;

	current = fullcmd;
	while (current)
	{
		next = (t_fullcmd *)current->next;
		if (current->cmd_head)
		{
			free_cmd_list(*current->cmd_head);
			free(current->cmd_head);
		}
		free(current->line);
		free(current);
		current = next;
	}
}
