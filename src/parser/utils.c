#include "../../includes/minishell.h"

void    skip_word(int *i, char *str)
{
    while ((str[*i] < 9 || str[*i] > 13) && str[*i] != ' ')
        (*i)++;
}

int    is_tabular(char c, char d)
{
    if (((c >= 9 && c <= 13) || c == ' ') && ((d >= 9 && d <= 13) || d == ' ' || d == '\0'))
        return (1);
    else
        retrun (0);
}

// Helper function for handling double quotes
int handle_double_quotes(char *str, char *str_clean, int *i, int *j)
{
    int to_expand;

    str_clean[(*j)++] = str[(*i)++]; // Copy the opening quote
    while (str[*i] != '\"' && str[*i] != '\0')
    {
        if (str[*i] == '$')
			expander(str, i);
        else
            str_clean[(*j)++] = str[(*i)++]; // Copy character inside quotes
    }
    if (str[*i] == '\"') // Closing double quote
        str_clean[(*j)++] = str[(*i)++];
    else // Error: unclosed double quote
        return -1;
    return 0;
}

// Helper function for handling single quotes
int handle_single_quotes(char *str, char *str_clean, int *i, int *j)
{
    str_clean[(*j)++] = str[(*i)++]; // Copy the opening quote

    while (str[*i] != '\'' && str[*i] != '\0')
        str_clean[(*j)++] = str[(*i)++];
    if (str[*i] == '\'') // Closing single quote
        str_clean[(*j)++] = str[(*i)++];
    else // Error: unclosed single quote
        return -1;
    return 0;
}

void start(t_general *all, char **build)
{
    all->env_v = build_env(build);
    all->export_v = build_env(build);
    //all->tmp = "\n";
}

void expand_variable(char *str, int *i, char *str_clean, int *j)
{
	char *var_name;
	char *var_value;
	int k;
	int l;

	var_name = malloc(sizeof(char) * 256);
	if (!var_name)
		return (0);

	// Skip the '$' character
	(*i)++;
	k = 0;
	// Extract variable name
	while (str[*i] && (isalnum(str[*i]) || str[*i] == '_'))
	{
		if (k < 255)
		{
			var_name[k] = str[*i];
			k++;
		}
		(*i)++;
	}
	var_name[k] = '\0';

	// Get the variable value from the environment
	var_value = getenv(var_name);

	// If variable exists, append its value to str_clean
	if (var_value)
	{
		l = 0;
		while (var_value[l])
		{
			str_clean[(*j)++] = var_value[l];
			l++;
		}
	}
	// If variable does not exist, do nothing (empty expansion)
	free(var_name);
}

int expand_variable_length(char *str, int *i)
{
	char var_name[256];
	char *var_value;
	int k;

	(*i)++; // Skip the '$' character

	// Extract variable name
	while (str[*i] && (isalnum(str[*i]) || str[*i] == '_'))
	{
		if (k < 255) // Prevent buffer overflow
			var_name[k++] = str[*i];
		(*i)++;
	}
	var_name[k] = '\0';

	// Get the variable value from the environment
	var_value = getenv(var_name);

	// Return the length of the expanded value, or 0 if the variable doesn't exist
	if (var_value)
		return strlen(var_value);
	else
		return 0;
}