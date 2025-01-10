#include "../../includes/mini.h"

void display_command_info(t_fullcmd *cmd, int cmd_num)
{
	printf("\nCommand #%d:\n", cmd_num);
	printf("Original string: \"%s\"\n", cmd->line);
	printf("Parsed command: ");
	print_cmd_list(*cmd->cmd_head);
	printf("----------------------------------------\n");
}

void display_all_commands(t_fullcmd *list)
{
	t_fullcmd	*current;
	int			cmd_num;

	current = list;
	cmd_num = 1;
	while (current)
	{
		display_command_info(current, cmd_num);
		current = (t_fullcmd *)current->next;
		cmd_num++;
	}
}

int initialize_shell(char *line, t_fullcmd **list)
{
	t_quotes quotes;

	// if (argc < 1)
	// {
	// 	printf("Usage: %s \"command string\"\n", argv[0]);
	// 	return (1);
	// }
	
	if (pipe_checker(line))
		return (1);

	if (red_checker(line))
		return (1);

	*list = NULL;
	*list = split_string_to_list(line, *list, &quotes);
	if (!*list)
		return (1);

	if (fill_cmd_lists(*list))
	{
		printf("Error filling cmd lists\n");
		free_all_lists(*list);
		return (1);
	}
	return (0);
}

// int main(int argc, char **argv, char **envp)
// {
// 	t_fullcmd *list;

// 	if (initialize_shell(argc, argv, &list))
// 		return (1);
// 	//display_all_commands(list);
// 	execute_line(list, envp);
// 	free_all_lists(list);
// 	return (0);
// }