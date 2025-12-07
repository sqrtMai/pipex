
#include "includes/pipex.h"

void first_process(t_list *lst, int **fds, char **argv, char **envp)
{
	char	*full_path;

	if (lst->absolute == 0)
	{
		full_path = ft_strjoin(lst->path, lst->cmd);
		if (check_cmd(full_path))
		{
			command_not_found(lst->args[0], argv[lst->index]);
			return (close(fds[0][1]), free_fd(fds, lst->total_args), free_list(&lst), exit(127));
		}
	}
	else
	{
		full_path = lst->cmd;
		if (check_cmd(full_path))
		{
			file_or_directory(full_path, argv[2]);
			return (close(fds[0][1]), free_fd(fds, lst->total_args), free_list(&(lst)), exit(127));
		}
	}
	dup2(lst->infile, 0);
	dup2(fds[0][1], 1);
	if (execve(full_path, lst->args, envp) < 0)
		return (close(fds[0][1]), free_fd(fds, lst->total_args), free_list(&lst), exit(1));
}

void closes(int fd1, int fd2)
{
	close(fd1);
	close(fd2);
}
void middle_process(int **fds, t_list *lst, char **envp, char **argv)
{
	char	*full_path;

	if (lst->absolute == 0)
	{
		full_path = ft_strjoin(lst->path, lst->cmd);
		if (check_cmd(full_path))
		{
			command_not_found(lst->args[0], argv[lst->index]);
			return (closes(fds[(lst->index - 2)][1], fds[(lst->index - 2 - 1)][0]), free_fd(fds, lst->total_args), free_list(&lst), exit(127));
		}
	}
	else
	{
		full_path = lst->cmd;
		if (check_cmd(full_path))
		{
			file_or_directory(full_path, argv[lst->index]);
			return (closes(fds[(lst->index - 2)][1], fds[(lst->index - 2 - 1)][0]), free_fd(fds, lst->total_args), free_list(&lst), exit(127));
		}
	}
	dup2(fds[(lst->index - 2)][1], 1);
	dup2(fds[(lst->index - 2 - 1)][0], 0);
	if (execve(full_path, lst->args, envp) < 0)
		return (closes(fds[(lst->index - 2)][1], fds[(lst->index - 2 - 1)][0]),free_fd(fds, lst->total_args),  free_list(&lst), exit(1));
}

void	last_process(int **fds, t_list *lst, char **envp, char **argv)
{
	char	*full_path;

	if (lst->absolute == 0)
	{
		full_path = ft_strjoin(lst->path, lst->cmd);
		if (check_cmd(full_path))
		{
			command_not_found(lst->args[0], argv[lst->index]);
			return (close(fds[(lst->index - 2 - 1)][0]), free_fd(fds, lst->total_args), free_list(&lst), exit(127));
		}
	}
	else
	{
		full_path = lst->cmd;
		if (check_cmd(full_path))
		{
			file_or_directory(full_path, argv[lst->index]);
			return (close(fds[(lst->index - 2 - 1)][0]), free_fd(fds, lst->total_args), free_list(&lst), exit(127));
		}
	}
	dup2(lst->outfile, 1);
	dup2(fds[(lst->index - 2 - 1)][0], 0);
	if (execve(full_path, lst->args, envp) < 0)
		return (close(fds[lst->index - 2 - 1][0]), free_fd(fds, lst->total_args), free_list(&lst), exit(1));
}

void tree_of_process(int **fds, t_list *lst, char **argv, char **envp)
{
	int current_process;

	current_process = lst->index - 2;
	if (current_process == 0)
		first_process(lst, fds, argv, envp);
	else if (current_process > 0 && current_process < (lst->total_args - 1))
		middle_process(fds, lst, envp, argv);
	else if (current_process == (lst->total_args - 1))
		last_process(fds, lst, envp, argv);
}
