#include "../../includes/mini.h"

int	handle_quotes(char c, int *in_single_quote, int *in_double_quote)
{
	if (c == '"' && !(*in_single_quote))
		*in_double_quote = !(*in_double_quote);
	else if (c == '\'' && !(*in_double_quote))
		*in_single_quote = !(*in_single_quote);
	return (*in_single_quote && *in_double_quote);
}

void	set_squotes(t_quotes *quotes, char *str)
{
	quotes->in_single_quote = 0;
	quotes->in_double_quote = 0;
	quotes->start = str;
	quotes->end = str;
}
