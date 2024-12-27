#include "../../includes/mini.h"

static int	direct_path(char *cmd)
{
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (access(cmd, X_OK) == 0)
			return (0);
	}
	return (1);
}

static char *find_path_free(char **all_path, char *full_path)
{
	int	i;

	i = 0;
	while (all_path[i++])
		free(all_path[i]);
	free(all_path);
	return (full_path);
}

// Trova il path completo di un comando
char *find_path(char *cmd)
{
	char	*path;
	char	**all_path;
	int		i;

	path = NULL;
	i = 0;
	if (!direct_path(cmd))
		return (strdup(cmd));
	path = getenv("PATH");
	if (!path)
		return (NULL);
	all_path = ft_split(path, ':');
	if (!all_path)
		return (NULL);
	while (all_path[i++])
	{
		all_path[i] = ft_strjoin(all_path[i], ft_strjoin(ft_strdup("/"), cmd));
		if (access(all_path[i], F_OK | X_OK) == 0)
		{
			path = ft_strdup(all_path[i]);
			return (find_path_free(all_path, path));
		}
	}
	return (find_path_free(all_path, NULL));
}
