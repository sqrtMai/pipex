#include "includes/pipex.h"

void main_process(int fd, t_list *lst)
{
	char *full_path;
	int test;
	full_path = ft_strjoin(lst->path, lst->cmd2);
	dup2(lst->outfile, 1);
	dup2(fd, 0);
	test = fork();
	if (test == 0)
		execve(full_path, lst->args2, NULL);
	else
	{
		waitpid(test, NULL, 0);
		close(fd);
	}

}

void child_process(int fd, t_list *lst)
{
	char *full_path;
	int test;
	full_path = ft_strjoin(lst->path, lst->cmd1);
	dup2(lst->infile, 0);
	dup2(fd, 1);
	close(fd);
	test = fork();
	if (test == 0)
		execve(full_path, lst->args1, NULL);
	else
	{
		waitpid(test, NULL, 0);
		close(fd);
	}
}
int check_cmd(char *path, char *cmd)
{
	char *full_path;

	full_path = ft_strjoin(path, cmd);
	if (access(full_path, X_OK) < 0)
		return (free(full_path), 1);
	else
		return (free(full_path), 0);
}

int main(int argc, char **argv, char **envp)
{
	int fd[2];
	pid_t id;
	pid_t id2;
	t_list *lst;

	if (argc != 5)
		return 1;
	lst = ft_lstnew_px(argv[2], argv[3], argv[1], argv[4], envp);
	if (!lst)
		return 1;
	if (lst->infile < 0 || lst->outfile < 0)
		return (free_list(&lst), perror("open"), 1);
	pipe(fd);
	id = fork();
	if (id != 0)
		id2 = fork();
	if (id == 0)
		return (close(fd[0]), child_process(fd[1], lst), 0);
	if (id != 0 && id2 != 0)
		close(fd[1]);
	if (id2 == 0)
	{
		close(fd[1]);
		return (main_process(fd[0], lst), 0);
	}
	else
	{
		waitpid(id, NULL, 0);
		waitpid(id2, NULL, 0);
		close(lst->infile);
		close(lst->outfile);
		free_list(&lst);
		close(fd[0]);
		close(fd[1]);
	}

	return 0;
}
