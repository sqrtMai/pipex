#include "includes/pipex.h"

int free_and_continue(char *s)
{
    free(s);
    return 1; // toujours vrai
}

void free_everything(char **str)
{
	int i;

	i = 0;
	while (str[i])
		free(str[i++]);
	if (str)
		free(str);
}

void free_list(t_list **lst)
{
	free((*lst)->path);
	free((*lst)->cmd1);
	free((*lst)->cmd2);
	free_everything((*lst)->args1);
	free_everything((*lst)->args2);
	free(*lst);
}

char **ft_strstrdup(char *str)
{
	char **pathes;

	pathes = malloc((1 + 1) * sizeof(char *));
	pathes[0] = ft_strdup(str);
	pathes[1] = NULL;
	return (pathes);

}

char *find_path(char **envp, char *cmd)
{
	char *path;
	char **pathes;
	int j;
	int i;

	i = 0;
	j = 0;
	while (!ft_strnstr(envp[i], "PATH", 4) && envp[i])
		i++;
	if (!envp[i])
		return NULL;
	path = ft_strdup(&envp[i][5]);
	if (ft_strchr(path, ':'))
		pathes = ft_split(path, ':');
	else
		pathes = ft_strstrdup(path);
	free(path);
	path = ft_strjoin((const char *)pathes[j], cmd);
	while (access(path, F_OK) < 0 && pathes[j++] && free_and_continue(path))
		path = ft_strjoin((const char *)pathes[j], cmd);
	free(path);
	path = ft_strdup(pathes[j]);
	return (free_everything(pathes), path);
}

