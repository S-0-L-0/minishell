#include "../../includes/mini.h"

void	skip_spaces(t_quotes *quotes)
{
	while (*quotes->end == ' ')
		quotes->end++;
}

void	trim_end_spaces(char *start, char *end)
{
	while (end > start && *(end - 1) == ' ')
		end--;
}

t_fullcmd *split_string_to_list(char *str, t_fullcmd *head, t_quotes *quotes)
{
	t_fullcmd	*current;

	current = head;
	set_squotes(quotes, str);
	while (*quotes->end)
	{
		if (handle_quotes(*quotes->end, &quotes->in_single_quote, &quotes->in_double_quote))
			return (printf(QTERR), NULL);
		
		if (*quotes->end == '|' && !quotes->in_single_quote && !quotes->in_double_quote)
		{
			if (quotes->end > quotes->start)
			{
				char *tmp_end = quotes->end;
				trim_end_spaces(quotes->start, tmp_end);
				if (tmp_end > quotes->start)
					handle_newnode(&head, &current, quotes->start, tmp_end);
			}
			quotes->end++;
			skip_spaces(quotes);
			quotes->start = quotes->end;
		}
		else
			quotes->end++;
	}
	
	if (quotes->end > quotes->start)
	{
		char *tmp_end = quotes->end;
		trim_end_spaces(quotes->start, tmp_end);
		if (tmp_end > quotes->start)
			handle_newnode(&head, &current, quotes->start, tmp_end);
	}
	
	if (quotes->in_single_quote || quotes->in_double_quote)
		return (printf(QTERR), NULL);
	
	return (head);
}
