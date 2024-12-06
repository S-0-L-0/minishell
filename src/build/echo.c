#include "../../includes/minishell.h"

void ft_echo(char **args)
{
    int i = 1;       // Skip the command name
    int newline = 1; // Assume we want a newline by default

    // Check if the first argument is `-n`
    if (args[1] && strcmp(args[1], "-n") == 0)
    {
        newline = 0; // Suppress newline
        i++;
    }

    // Print the remaining arguments
    while (args[i])
    {
        printf("%s", args[i]);
        if (args[i + 1]) // Add a space between arguments
            printf(" ");
        i++;
    }

    if (newline) // Print newline if not suppressed
        printf("\n");
}
