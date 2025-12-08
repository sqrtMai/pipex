#include "includes/pipex.h"

int	free_and_continue(char *s)
{
	free(s);
	return (1);
}

void	free_everything(void **vector)
{
	int	i;

	i = 0;
	while (vector[i])
		free(vector[i++]);
	if (vector)
		free(vector);
}

void	free_list(t_list **lst)
{
	t_list	*temp;

	while ((*lst)->previous)
		*lst = (*lst)->previous;
	temp = *lst;
	while (temp)
	{
		if (temp->path && !temp->absolute)
			free(temp->path);
		if (temp->cmd && !temp->absolute)
			free(temp->cmd);
		if (temp->args)
			free_everything(((void **)temp->args));
		if ((*lst)->infile == 0)
			close((*lst)->infile);
		if ((*lst)->outfile == 0)
			close((*lst)->outfile);
		temp = temp->next;
		free(*lst);
		*lst = temp;
	}
}
