#include "includes/pipex.h"

void	init_infile(t_list *lst, char *infile)
{
	lst->infile = open(infile, O_RDONLY);

	if ((access(infile, R_OK) < 0 && access(infile, F_OK) == 0))
	{
		ft_printf("%s: Permission denied\n", infile);
		return ;
	}
	if (lst->infile < 0)
		ft_printf("%s: no such file or directory\n", infile);
}

void	init_outfile(t_list *lst, char *outfile)
{
	lst->outfile = open(outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (access(outfile, W_OK) < 0 && access(outfile, F_OK) == 0)
	{
		ft_printf("%s: Permission denied\n", outfile);
		return ;
	}
	if (lst->outfile < 0)
		ft_printf("%s: a problem has occured with opening outfile\n", outfile);
}
