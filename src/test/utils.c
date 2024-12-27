#include "../../includes/mini.h"

void	print_cmd_list(t_cmd *cmd)
{
	t_cmd *current;

	current = cmd;
	printf("[ ");
	while (current)
	{
		printf("%s", current->word);
		if (current->next)
			printf(" -> ");
		current = current->next;
	}
	printf(" ]\n");
}

int	fill_cmd_lists(t_fullcmd *fullcmd)
{
	t_fullcmd    *current_fcmd;

	current_fcmd = fullcmd;
	while (current_fcmd)
	{
		current_fcmd->cmd_head = malloc(sizeof(t_cmd *));
		if (!current_fcmd->cmd_head)
			return (1);
		*current_fcmd->cmd_head = NULL;
		if (process_line(current_fcmd->line, current_fcmd->cmd_head))
			return (1);
		current_fcmd = (t_fullcmd *)current_fcmd->next;
	}
	return (0);
}