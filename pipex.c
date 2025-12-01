#include "includes/pipex.h"

void main_process(int fd, t_list *lst, char **envp)
{
	char *full_path;

	if (lst->next->absolute == 0)
	{
		full_path = ft_strjoin(lst->next->path, lst->next->cmd);
		if (check_cmd(full_path))
		{
			ft_printf("command not found: %s\n", lst->next->cmd);
			return (free_list(&lst, 2), exit(1));
		}
	}
	else
	{
		full_path = lst->next->cmd;
		if (check_cmd(full_path))
		{
			ft_printf("No such file or directory: %s\n", full_path);
			return (free_list(&lst, 2), exit(1));
		}
	}
	dup2(lst->outfile, 1);
	dup2(fd, 0);
	if (execve(full_path, lst->next->args, envp) < 0)
		return (free_list(&lst, 2), exit(1));
}

void child_process(int fd, t_list *lst, char **envp)
{
	char *full_path;

	if (lst->absolute == 0)
	{
		full_path = ft_strjoin(lst->path, lst->cmd);
		if (check_cmd(full_path))
		{
			ft_printf("command not found: %s\n", lst->cmd);
			return (free_list(&lst, 2), exit(1));
		}
	}
	else
	{
		full_path = lst->cmd;
		if (check_cmd(full_path))
		{
			ft_printf("No such file or directory: %s\n", full_path);
			return (free_list(&lst, 2), exit(1));
		}
	}
	dup2(lst->infile, 0);
	dup2(fd, 1);
	if (execve(full_path, lst->args, envp) < 0)
	{
		free_list(&lst, 2);
		exit(1);
	}

}
int check_cmd(char *full_path)
{

	if (!full_path)
		return 1;
	if (access(full_path, X_OK) < 0)
		return (1);
	else
		return (0);
}

int main(int argc, char **argv, char **envp)
{
	int fd[2];
	pid_t id;
	pid_t id2;
	t_list *lst;

	if (argc != 5)
		return 1;
	lst = NULL;
	init_list(&lst, argv, envp);
	pipe(fd);
	id = fork();
	if (id != 0)
		id2 = fork();
	if (id == 0)
		return (close(fd[0]), child_process(fd[1], lst, envp), 0);
	close(fd[1]);
	if (id2 == 0)
		return (main_process(fd[0], lst, envp), 0);
	else
		return (waitpid(id, NULL, 0), waitpid(id2, NULL, 0), close(fd[0]), free_list(&lst, 2), 0);
}
