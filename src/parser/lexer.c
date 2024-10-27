#include "../../includes/minishell.h"

int	int_clean_input(char *str)
{
	int i;
	int	count;

	i = 0;
	count = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i]==' ')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			while ((str[i]<9||str[i]>13) && str[i] != ' ')
				i++; 
		}
		else if (str[i] == '"')
		{
			i++;
			count++;
			while (str[i] != '\"')
			{
				if (str[i] == '$')
				{
					while ((str[i]<9||str[i]>13) && str[i] != ' ')
						i++; 
				}
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
		else if (((str[i] >= 9 && str[i] <= 13) || str[i]==' ')&&((str[i+1] >= 9 && str[i+1] <= 13) || str[i+1] == ' ' || str[i+1] == '\0'))
			i++;
		else
		{
			i++;
			count++;
		}
	}
	return(count);
}

// Every iteration can be done in functions sending pointers
char *lexer(char *str)
{
	int i;
	int j;
	int	to_expand;
	char *str_clean;

	i = 0;
	str_clean = malloc(sizeof (int) * int_clean_input(str));
	while ((str[i] >= 9 && str[i] <= 13) || str[i]==' ')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			to_expand = 0;
			while ((str[i]<9||str[i]>13) && str[i] != ' ')
			{	
				i++;
				to_expand++;
			}
			// expander(str, &i, &to_expand, _env);
		}
		else if (str[i] == '\"')
		{
			str_clean[j] = str[i];
			i++;
			j++;
			while (str[i] != '\"')
			{
				if (str[i] == '$')
				{
					to_expand = 0;
					while ((str[i]<9||str[i]>13) && str[i] != ' ')
					{	
						i++;
						to_expand++;
					}
					// expander(str, &i, &to_expand, _env);
				}
				str_clean[j] = str[i];
				i++;
				j++;
				if (str[i] == '\0')
					return ("ERROR-CLOSE DOUBLE QUOTES");
			}
			str_clean[j] = str[i];
			i++;
			j++;
		}
		else if (str[i] == '\'')
		{
			str_clean[j] = str[i];
			i++;
			j++;
			while (str[i] != '\'')
			{
				str_clean[j] = str[i];
				i++;
				j++;
				if (str[i] == '\0')
					return ("ERROR-CLOSE SINGLE QUOTES");
			}
			str_clean[j] = str[i];
			i++;
		}
		else if (((str[i] >= 9 && str[i] <= 13) || str[i]==' ')&&((str[i+1] >= 9 && str[i+1] <= 13) || str[i+1] == ' ' || str[i+1] == '\0'))
			i++;
		else
		{
			str_clean[j] = str[i];
			i++;
			j++;
		}
	}
	str_clean[j] = '\0';
	return (str_clean);
}


// Other suggested functions
int check_double_single_quote(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"')
		{
			while (str[i] != '\0')
			{
				if(str[i] == '"')
					break;
				i++;
			}
			return (0);
		}
		if (str[i] == '\'')
		{
			while (str[i] != '\0')
			{
				if(str[i] == '\'')
					break;
				i++;
			}
			return (0);
		}
		i++;
	}
	return (1);
}

char *double_quote()
{

}

char *single_quote()
{

}