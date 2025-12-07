/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mai <mai@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 16:17:01 by bbouarab          #+#    #+#             */
/*   Updated: 2025/12/07 17:20:43 by mai              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

int	free_and_continue(char *s)
{
	free(s);
	return (1);
}

void	free_everything(void **vector)
{
	int	i;

	i = 0;
	while (vector[i])
		free(vector[i++]);
	if (vector)
		free(vector);
}

void	free_list(t_list **lst)
{
	t_list	*temp;

	while ((*lst)->previous)
		*lst = (*lst)->previous;

	temp = *lst;
	//printf("%p\n", temp->next);
	while (temp)
	{
		if (temp->path && !temp->absolute)
			free(temp->path);
		if (temp->cmd && !temp->absolute)
			free(temp->cmd);
		if (temp->args)
			free_everything(((void **)temp->args));
		if ((*lst)->infile)
			close((*lst)->infile);
		if ((*lst)->outfile)
			close((*lst)->outfile);
		temp = temp->next;
		free(*lst);
		*lst = temp;
	}
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
