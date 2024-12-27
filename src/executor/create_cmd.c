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
		size ++;
		current = current->next;
	}
	cmd = malloc(sizeof(char *) * (size + 1));
	if (!cmd)
		return (NULL);
	while (cmd_list)
	{
		cmd[i] = strdup(cmd_list->word);
		cmd_list = cmd_list->next;
		i++;
	}
	cmd[i] = NULL;
	return (cmd);
}
