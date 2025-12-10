/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 16:17:01 by bbouarab          #+#    #+#             */
/*   Updated: 2025/12/10 14:32:52 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

size_t	argvlen(char **argv)
{
	size_t	size_of_argv;

	size_of_argv = 0;
	while (argv[size_of_argv])
		size_of_argv++;
	return (size_of_argv);
}

char	**ft_strstrdup(char *str)
{
	char	**pathes;

	pathes = malloc((1 + 1) * sizeof(char *));
	pathes[0] = ft_strdup(str);
	pathes[1] = NULL;
	return (pathes);
}

char	*find_path(char **envp, char *cmd)
{
	char	*path;
	char	**pathes;
	int		j;
	int		i;

	if (!cmd)
		return (NULL);
	i = 0;
	j = 0;
	while (!ft_strnstr(envp[i], "PATH", 4) && envp[i])
		i++;
	if (!envp[i])
		return (NULL);
	path = ft_strdup(&envp[i][5]);
	pathes = ft_split(path, ':');
	free(path);
	path = ft_strjoin((const char *)pathes[j], cmd);
	while (pathes[j++] && access(path, F_OK) < 0 && free_and_continue(path))
		path = ft_strjoin((const char *)pathes[j], cmd);
	free(path);
	path = ft_strdup(pathes[--j]);
	return (free_everything(((void **)pathes)), path);
}
