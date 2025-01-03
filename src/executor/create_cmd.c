#include "../../includes/mini.h"

char **make_command(t_cmd *cmd_list)
{
	t_cmd	*current;
	char	**cmd;
	int		size;
	int		i;

	size = 0;
	i = 0;
	current = cmd_list;
	while (current)
	{
		if (current->is_arg)
			size ++;
		else 
			size --;
		current = current->next;
	}
	if(size == 0)
		return(NULL);
	cmd = malloc(sizeof(char *) * (size + 1));
	if (!cmd)
		return (NULL);
	while (cmd_list)
	{
		if (cmd_list->is_arg)
		{
			cmd[i] = strdup(cmd_list->word);
			i++;
		}
		else
			cmd_list = cmd_list->next;
		cmd_list = cmd_list->next;
	}
	cmd[i] = NULL;
	return (cmd);
}
