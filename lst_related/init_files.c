/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 14:28:37 by bbouarab          #+#    #+#             */
/*   Updated: 2025/12/10 14:28:46 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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
	if (lst->here_doc == 0)
		lst->outfile = open(outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (lst->here_doc == 1 && lst->i > 2)
		lst->outfile = open(outfile, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (access(outfile, W_OK) < 0 && access(outfile, F_OK) == 0)
	{
		ft_printf("%s: Permission denied\n", outfile);
		return ;
	}
	if (lst->outfile < 0)
		ft_printf("%s: a problem has occured with opening outfile\n", outfile);
}
