#include "../../includes/minishell.h"

void ft_exit(char **args)
{
    int exit_code = 0;

    if (args[1]) // If an exit code is provided
    {
        for (int i = 0; args[1][i]; i++)
        {
            if (!isdigit(args[1][i])) // Ensure the argument is numeric
            {
                ft_printf("exit: numeric argument required\n");
                exit(255);
            }
        }
        exit_code = atoi(args[1]); // Convert the argument to an integer
    }

    // Print exit and terminate the shell
    printf("exit\n");
    exit(exit_code);
}
