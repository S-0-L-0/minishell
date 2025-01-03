#include "../../includes/mini.h"

void	free_matrix(char **matrix)
{
	int	rows;

	rows = 0;
	while (matrix[rows])
	{
		free(matrix[rows]);
		rows ++;
	}
	free(matrix);
}

void	set_pipe(t_pipe *pipe)
{
	pipe->tmp_fd = 0;
	pipe->std_in = dup(0);
	pipe->std_out = dup(1);
}

void	print_cmd(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		printf("%d argument %s\n", i, cmd[i]);
		i++;
	}
	return ;
}