#include "pipex_bonus.h"

void first_process(int **fds, int current_process)
{
	int x = 0;
	x++;
	write(fds[0][1], &x, sizeof(int));
	close(fds[0][1]);
	exit(1);
}

void middle_process(int **fds, int current_process)
{
	int x = 0;
	read(fds[current_process - 1][0], &x, sizeof(int));
	// printf("first : %d\n", x);
	x++;
	write(fds[current_process][1], &x, sizeof(int));

	close(fds[current_process - 1][0]);
	close(fds[current_process][1]);

	exit(1);
}

void last_process(int **fds, int current_process)
{
	int x = 0;
	// printf("return de read : %d\n", read(fds[1][0], &x, sizeof(int)));
	read(fds[current_process - 1][0], &x, sizeof(int));
	printf("last : %d\n", x);
	close(fds[current_process - 1][0]);
	exit(1);
}

void tree_of_process(int **fds, int current_process)
{
	printf("Current process = %d\n", current_process);
	if (current_process == 0)
		first_process(fds, current_process);
	else if (current_process > 0 && current_process < (total_args - 1))
		middle_process(fds, current_process);
	else if (current_process == (total_args - 1))
		last_process(fds, current_process);
}
