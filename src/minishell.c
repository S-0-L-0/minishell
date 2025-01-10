#include "../includes/mini.h"
#include "../includes/print.h"

int main(int argc, char **argv, char **envp)
{
	t_fullcmd *list;
	char *line;
	if (argc && argv)
	{
		printf(RED "%s", HELLO RESET);
		while (1)
		{
			// Leggi l'input
			line = readline(RED "minishell> "RESET);
			write(1, "prima\n", 6);
			if (!line)
				break;
			// Aggiungi l'input alla history
			if (line[0] != '\0')
				add_history(line);
			if (initialize_shell(line, &list))
				return (1);
			execute_line(list, envp);
			write(1, "dopo\n", 5);
		}
			free_all_lists(list);
	}
	return 0;
}