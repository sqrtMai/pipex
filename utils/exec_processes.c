/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 14:31:19 by bbouarab          #+#    #+#             */
/*   Updated: 2025/12/10 14:32:07 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	first_process(t_list *lst, int **fds, char **argv, char **envp)
{
	char	*full_path;

	if (lst->absolute == 0)
		full_path = check_absolute_0(fds, lst, argv, fds[0][1]);
	else
		full_path = check_absolute_1(fds, lst, argv, fds[0][1]);
	if (dup2(lst->infile, 0) < 0)
	{
		if (lst->absolute == 0 && full_path)
			free(full_path);
		return (close(fds[0][1]),
		free_fd(fds, lst->total_args), free_list(&lst), exit(1));
	}
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

void	middle_process(int **fds, t_list *lst, char **envp, char **argv)
{
	char	*full_path;

	if (lst->absolute == 0)
		full_path = check_absolute_middle_0(fds, lst, argv);
	else
		full_path = check_absolute_middle_1(fds, lst, argv);
	if (dup2(fds[(lst->i - 2)][1], 1) < 0)
	{
		if (lst->absolute == 0 && full_path)
			free(full_path);
		return (closes(fds[(lst->i - 2)][1], fds[(lst->i - 2 - 1)][0]),
		free_fd(fds, lst->total_args), free_list(&lst), exit(1));
	}
	if (dup2(fds[(lst->i - 2 - 1)][0], 0) < 0)
	{
		if (lst->absolute == 0 && full_path)
			free(full_path);
		return (closes(fds[(lst->i - 2)][1], fds[(lst->i - 2 - 1)][0]),
		free_fd(fds, lst->total_args), free_list(&lst), exit(1));
	}
	if (execve(full_path, lst->args, envp) < 0)
		return (closes(fds[(lst->i - 2)][1], fds[(lst->i - 2 - 1)][0]),
		free_fd(fds, lst->total_args), free_list(&lst), exit(1));
}

void	last_process(int **fds, t_list *lst, char **envp, char **argv)
{
	char	*full_path;

	if (lst->absolute == 0)
		full_path = check_absolute_0(fds, lst, argv, fds[lst->i - 2 - 1][0]);
	else
		full_path = check_absolute_1(fds, lst, argv, fds[lst->i - 2 - 1][0]);
	if (dup2(lst->outfile, 1) < 0)
	{
		if (lst->absolute == 0 && full_path)
			free(full_path);
		return (close(fds[lst->i - 2 - 1][0]),
		free_fd(fds, lst->total_args), free_list(&lst), exit(1));
	}
	if (dup2(fds[(lst->i - 2 - 1)][0], 0) < 0)
	{
		if (lst->absolute == 0 && full_path)
			free(full_path);
		return (close(fds[lst->i - 2 - 1][0]),
		free_fd(fds, lst->total_args), free_list(&lst), exit(1));
	}
	if (execve(full_path, lst->args, envp) < 0)
		return (close(fds[lst->i - 2 - 1][0]), free_fd(fds, lst->total_args),
		free_list(&lst), exit(1));
}

void	tree_of_process(int **fds, t_list *lst, char **argv, char **envp)
{
	int	current_process;

	current_process = lst->i - 2;
	if (current_process == 0 && lst->here_doc == 0)
		first_process(lst, fds, argv, envp);
	if (current_process == 0 && lst->here_doc == 1)
		here_doc(lst, fds, argv, envp);
	else if (current_process > 0 && current_process < (lst->total_args - 1))
		middle_process(fds, lst, envp, argv);
	else if (current_process == (lst->total_args - 1))
		last_process(fds, lst, envp, argv);
}

int	create_process(int **fds, t_list *lst, char **argv, char **envp)
{
	int		status;
	int		current_process;
	t_list	*first;

	status = 0;
	current_process = lst->i - 2;
	first = lst;
	while (lst)
	{
		lst->pid = fork();
		if (lst->pid == 0)
		{
			tree_of_closing(fds, current_process, lst->total_args);
			tree_of_process(fds, lst, argv, envp);
		}
		lst = lst->next;
		current_process++;
	}
	close_all_pipes(fds, first->total_args);
	while (first)
	{
		waitpid(first->pid, &status, 0);
		first = first->next;
	}
	return (status);
}
