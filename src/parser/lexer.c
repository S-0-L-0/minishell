#include "../../includes/minishell.h"

int int_clean_input(char *str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			// Use the expand_variable_length function to get the length of the expanded variable
			count += expand_variable_length(str, &i);
		}
		else if (str[i] == '"')
		{
			i++;
			count++;
			while (str[i] != '\"')
			{
				if (str[i] == '$')
					count += expand_variable_length(str, &i);
				i++;
				count++;
			}
			i++;
			count++;
		}
		else if (str[i] == '\'')
		{
			i++;
			count++;
			while (str[i] != '\'')
			{
				i++;
				count++;
			}
			i++;
			count++;
		}
		else if (is_tabular(&str[i], &str[i + 1]))
			i++;
		else
		{
			i++;
			count++;
		}
	}
	return (count);
}

char *lexer(char *str)
{
	int i;
	int j;
	char *str_clean;

	j = 0;
	str_clean = malloc(sizeof(char) * (int_clean_input(str) + 1));
	if (!str_clean)
		return (NULL);
	i = 0;
	// Skip initial whitespace
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;

	// Process the string
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			// Expand environment variable
			expand_variable(str, &i, str_clean, &j);
		}
		else if (str[i] == '\"')
		{
			// Handle double quotes
			if (handle_double_quotes(str, str_clean, &i, &j) == -1)
				return (NULL);
		}
		else if (str[i] == '\'')
		{
			// Handle single quotes
			if (handle_single_quotes(str, str_clean, &i, &j) == -1)
				return (NULL);
		}
		else if (is_tabular(str[i], str[i + 1]))
		{
			i++;
		}
		else
		{
			// Copy regular characters
			str_clean[j++] = str[i++];
		}
	}

	str_clean[j] = '\0';
	return (str_clean);
}