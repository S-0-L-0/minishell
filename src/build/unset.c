#include "../../includes/minishell.h"

void ft_unset(char **args)
{
    if (args[1] == NULL) // No variable provided
    {
        ft_printf("unset: not enough arguments\n");
        return;
    }

    for (int i = 1; args[i]; i++)
    {
        if (unsetenv(args[i]) != 0) // Attempt to unset the variable
        {
            perror("unset");
        }
    }
}