#include "pipex_bonus.h"

int **malloc_fds(void)
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

void open_pipes(int **fds)
{
	int i = 0;
	while (i <= total_args - 2)
	{
		pipe(fds[i]);
		i++;
	}
}

void create_process(pid_t *pids, int **fds)
{
	int i = 0;
	int x = 0;
	while (i < total_args)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			tree_of_closing(fds, i);
			tree_of_process(fds, i);
		}
		else
			waitpid(pids[i], NULL, 1);
		i++;
	}
}

void close_all_pipes(int **fds)
{
	int i = 0;
	int j;
	while (i < total_args)
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

int main(void)
{

	int **fds = malloc_fds();
	pid_t *pids = malloc(total_args * sizeof(pid_t));
	open_pipes(fds);
	create_process(pids, fds);
}
