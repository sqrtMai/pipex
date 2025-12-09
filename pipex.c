/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 16:16:53 by bbouarab          #+#    #+#             */
/*   Updated: 2025/12/09 10:15:31 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

int **malloc_fds(int total_args)
{
	int **fds;
	int i = 0;

	fds = malloc((total_args - 1) * sizeof(int *));
	while (i <= total_args - 2)
	{
		fds[i] = malloc(2 * sizeof(int));
		i++;
	}
	return fds;
}

void open_pipes(int **fds, int total_args)
{
	int i = 0;
	while (i <= total_args - 2)
	{
		pipe(fds[i]);
		i++;
	}
}
void close_all_pipes(int **fds, int total_args)
{
	int i = 0;
	int j;
	while (i <= total_args - 2)
	{
		j = 0;
		while (j < 2)
		{
			close(fds[i][j]);
			j++;
		}
		i++;
	}
}

int	check_cmd(char *full_path)
{
	if (!full_path)
		return (1);
	if (access(full_path, X_OK) < 0)
		return (1);
	else
		return (0);
}

void free_fd(int **fds, int total_args)
{
	int	i;

	i = 0;
	while (i <= total_args - 2)
		free(fds[i++]);
	if (fds)
		free(fds);
}

int	main(int argc, char **argv, char **envp)
{
	int		total_args;
	int		**fds;
	int		status;
	t_list	*lst;

	if (argc < 5)
		return (1);
	lst = NULL;
	total_args = argc - 3;
	init_list(&lst, argv, envp, total_args);
	total_args -= lst->here_doc;
	fds = malloc_fds(total_args);
	open_pipes(fds, total_args);
	status = create_process(fds, lst, argv, envp);
	if ((ft_lstlast(lst))->outfile < 0)
		return (free_fd(fds, total_args), free_list(&lst), 1);
	else
		return (free_fd(fds, total_args), free_list(&lst),
			WEXITSTATUS(status));
}
