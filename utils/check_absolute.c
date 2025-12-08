#include "includes/pipex.h"

char	*check_absolute_0(int **fds, t_list *lst, char **argv, int fd2)
{
	char	*full_path;

	full_path = ft_strjoin(lst->path, lst->cmd);
	if (check_cmd(full_path))
	{
		if (full_path)
			free(full_path);
		return (n_cmd(lst->args[0], argv[lst->i]), close(fd2)
			, free_fd(fds, lst->total_args), free_list(&lst), exit(127), NULL);
	}
	else
		return full_path;
}
char 	*check_absolute_1(int **fds, t_list *lst, char **argv, int fd2)
{
	char	*full_path;

	full_path = lst->cmd;
	if (check_cmd(full_path))
	{
		return (n_cmd(lst->args[0], argv[lst->i]), close(fd2)
			, free_fd(fds, lst->total_args), free_list(&lst), exit(127), NULL);
	}
	else
		return (full_path);
}


char	*check_absolute_middle_0(int **fds, t_list *lst, char **argv)
{
	char	*full_path;

	full_path = ft_strjoin(lst->path, lst->cmd);
	if (check_cmd(full_path))
	{
		if (full_path)
			free(full_path);
		return (n_cmd(lst->args[0], argv[lst->i]), closes(fds[(lst->i - 2)][1], fds[(lst->i - 2 - 1)][0])
			, free_fd(fds, lst->total_args), free_list(&lst), exit(127), NULL);
	}
	else
		return full_path;
}
char 	*check_absolute_middle_1(int **fds, t_list *lst, char **argv)
{
	char	*full_path;

	full_path = lst->cmd;
	if (check_cmd(full_path))
	{
		return (n_cmd(lst->args[0], argv[lst->i]) ,closes(fds[(lst->i - 2)][1], fds[(lst->i - 2 - 1)][0])
			, free_fd(fds, lst->total_args), free_list(&lst), exit(127), NULL);
	}
	else
		return (full_path);
}
