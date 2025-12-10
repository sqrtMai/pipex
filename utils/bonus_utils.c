/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 14:15:49 by bbouarab          #+#    #+#             */
/*   Updated: 2025/12/10 14:15:59 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	here_second(t_list *lst, int **fds, char **argv, char **envp)
{
	char	*full_path;

	if (lst->absolute == 0)
		full_path = check_absolute_0(fds, lst, argv, fds[0][1]);
	else
		full_path = check_absolute_1(fds, lst, argv, fds[0][1]);
	if (dup2(fds[0][1], 1) < 0)
	{
		if (lst->absolute == 0 && full_path)
			free(full_path);
		return (close(fds[0][1]),
		free_fd(fds, lst->total_args), free_list(&lst), exit(1));
	}
	if (execve(full_path, lst->args, envp) < 0)
		return (close(fds[0][1]), free_fd(fds, lst->total_args),
		free_list(&lst), exit(1));
}

void	here_doc(t_list *lst, int **fds, char **argv, char **envp)
{
	int		test;
	char	*gnl;

	gnl = get_next_line(0);
	test = open("/var/tmp/temp", O_RDWR | O_TRUNC | O_CREAT, 0644);
	while (ft_findstr(argv[2], gnl))
	{
		write(test, gnl, ft_strlen(gnl));
		free(gnl);
		gnl = get_next_line(0);
	}
	test = open("/var/tmp/temp", O_RDWR, 0644);
	if (dup2(test, 0) < 0)
	{
		return (close(fds[0][1]), close(test),
		free_fd(fds, lst->total_args), free_list(&lst), exit(1));
	}
	unlink("/var/tmp/temp");
	here_second(lst, fds, argv, envp);
}
