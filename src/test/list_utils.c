#include "../../includes/mini.h"

t_fullcmd	*create_newnode(char *start, char *end)
{
	t_fullcmd *new_node;
	
	new_node = (t_fullcmd *)malloc(sizeof(t_fullcmd));
	if (!new_node)
		return (NULL);
	new_node->line = strndup(start, end - start);
	if (!new_node->line)
	{
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	new_node->cmd_head = NULL;
	return (new_node);
}

void	handle_newnode(t_fullcmd **list_head, t_fullcmd **current, char *start, char *end)
{
	t_fullcmd *new_node;
	
	new_node = create_newnode(start, end);
	if (!new_node)
		return;
	if (*list_head == NULL)
	{
		*list_head = new_node;
		*current = *list_head;
	}
	else
	{
		(*current)->next = (struct s_fullcmd *)new_node;
		*current = (t_fullcmd *)(*current)->next;
	}
}
