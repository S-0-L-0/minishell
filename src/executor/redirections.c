#include "../../includes/mini.h"

int	check_red(char *str, char red_sign)
{
	int i;
	bool s_quote;
	bool d_quote;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	while(str[i])
	{
		if (str[i] == '\'' && !d_quote && !s_quote)
			s_quote = 1;
		else if (str[i] == '\'' && !d_quote && s_quote)
			s_quote = 0;
		else if (str[i] == '"' && !s_quote && !d_quote)
			d_quote = 1;
		else if (str[i] == '"' && !s_quote && d_quote)
			d_quote = 0;
		else if (str[i] == red_sign && !s_quote && !d_quote)
		{
			return(1);
		}
		i++;
	}
	return(0);
}

int	get_inputred_fd(t_cmd *cmd)
{
	int		i;
	int		s_quote;
	int		d_quote;
	t_cmd	*tmp;

	s_quote = 0;
	d_quote = 0;
	tmp = cmd;
	while (tmp)
	{
		i = 0;
		while(tmp->word[i])
		{
			if (tmp->word[i] == '\'' && !d_quote && !s_quote)
				s_quote = 1;
			else if (tmp->word[i] == '\'' && !d_quote && s_quote)
				s_quote = 0;
			else if (tmp->word[i] == '"' && !s_quote && !d_quote)
				d_quote = 1;
			else if (tmp->word[i] == '"' && !s_quote && d_quote)
				d_quote = 0;
			else if (tmp->word[i] == '<' && !s_quote && !d_quote)
			{
				printf("result: %s\n", tmp->next->word);
				return(open(tmp->next->word, O_RDONLY, 0644));
			}
			i++;
		}
		tmp = tmp->next;
	}
	return(0);
}