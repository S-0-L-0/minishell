#include "../../includes/mini.h"


static bool	check_red_arg(char *str, char c)
{
	char	*tmp;
	bool	flag;

	tmp = str;
	flag = false;
	while (*tmp)
	{
		if (ft_strchr(tmp, c) && flag == false)
		{
				tmp = ft_strchr(tmp, c);
				if (*(tmp + 1) == c)
					tmp = ft_strchr(tmp, c);
				flag = true;
		}
		else 
		{
			tmp ++; 
			if (ft_isprint(*tmp))
			{
				flag = false;
			}
		}
	}
	free(str);
	return (flag);
}



int	red_checker(char *str)
{
	int	i;

	i = 0;
	while (str)
	{
		if (ft_strchr(str, '|'))
			i = ft_strlen(str) - ft_strlen(ft_strchr(str, '|'));
		else
			i = ft_strlen(str);
		if (check_red_arg(ft_substr(str, 0, i), '<') || check_red_arg(ft_substr(str, 0, i), '>'))
		{
			perror("Error: Redirection error\n");
			return (1);
		}
		if (ft_strchr(str, '|'))
		{
			str = ft_strchr(str, '|');
			str++;
		}
		else
			break ;
	}
	return (0);
}

// void remove_redirection_nodes(t_cmd **head)
// {
//     t_cmd *current = *head;
//     t_cmd *temp;

//     while (current && current->next)
//     {
//         if (current->word[0] == '<')
//         {
//             temp = current->next->next;
//             free(current->word);
//             free(current->next->word);
//             free(current->next);
//             free(current);
//             *head = temp;
//             return;
//         }
//         current = current->next;
//     }
// }
