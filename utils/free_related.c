/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_related.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 14:32:23 by bbouarab          #+#    #+#             */
/*   Updated: 2025/12/10 14:32:24 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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

void	free_fd(int **fds, int total_args)
{
	int	i;

	i = 0;
	while (i <= total_args - 2)
		free(fds[i++]);
	if (fds)
		free(fds);
}

void	free_list(t_list **lst)
{
	t_list	*temp;

	while ((*lst)->previous)
		*lst = (*lst)->previous;
	temp = *lst;
	while (temp)
	{
		if (temp->path && !temp->absolute)
			free(temp->path);
		if (temp->cmd && !temp->absolute)
			free(temp->cmd);
		if (temp->args)
			free_everything(((void **)temp->args));
		if ((*lst)->infile == 0)
			close((*lst)->infile);
		if ((*lst)->outfile == 0)
			close((*lst)->outfile);
		temp = temp->next;
		free(*lst);
		*lst = temp;
	}
}
