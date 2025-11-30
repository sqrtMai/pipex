#include "includes/pipex.h"

void main_process(int fd, t_list *lst)
{
	int new_child;
	char *full_path;

	full_path = ft_strjoin(lst->path, lst->cmd2);
	dup2(fd, 0);
	dup2(lst->outfile, 1);
	new_child = fork();
	if (new_child == 0)
	{
		if (!execve(full_path, lst->args2, NULL))
			write(2, "test", 4);
	}
	else
	{
		free(full_path);
		close(fd);
		close(lst->outfile);
	}
}

void child_process(int fd, t_list *lst)
{
	char *full_path;

	full_path = ft_strjoin(lst->path, lst->cmd1);
	dup2(lst->infile, 0);
	dup2(fd, 1);
	execve(full_path, lst->args1, NULL);
}

/*peut être commencer à use des structures*/

int main(int argc, char **argv, char **envp)
{
	int fd[2];
	int id;
	t_list *lst;

	if (argc != 5)
		return 1;
	lst = ft_lstnew(argv[2], argv[3], argv[1], argv[4]);
	if (!lst)
		return (1);
	if (lst->infile < 0 || lst->outfile < 0)
		return (free_list(&lst), perror("open"), 1);
	pipe(fd);
	lst->path = find_path(envp, lst->cmd1);
	if (!lst->path)
		return (ft_printf("No argument has been found"), 1);
	id = fork();
	if (id == 0)
		return (close(fd[0]), child_process(fd[1], lst), 0);
	else
		return (close(fd[1]), main_process(fd[0], lst), free_list(&lst), 0);
}
