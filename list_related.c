/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_related.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 08:23:46 by bbouarab          #+#    #+#             */
/*   Updated: 2025/12/04 16:28:26 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

t_list	*init_nodes(void)
{
	t_list	*new_list;

	new_list = malloc(sizeof(t_list));
	if (!new_list)
		return (NULL);
	new_list->cmd = NULL;
	new_list->args = NULL;
	new_list->path = NULL;
	new_list->slash = "/";
	new_list->infile = 100;
	new_list->outfile = 100;
	new_list->absolute = 0;
	new_list->next = NULL;
	new_list->previous = NULL;
	return (new_list);
}

void	init_files(t_list *lst, char *infile, char *outfile)
{
	lst->infile = open(infile, O_RDONLY);
	lst->outfile = open(outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if ((access(infile, R_OK) < 0 && access(infile, F_OK) == 0))
		return (free_list(&lst, 2),
			ft_printf("%s: Permission denied\n", infile), exit(1));
	if (access(outfile, W_OK) < 0 && access(outfile, F_OK) == 0)
		return (free_list(&lst, 2),
			ft_printf("%s: Permission denied\n", outfile), exit(1));
	if (lst->infile < 0 || lst->outfile < 0)
		return (free_list(&lst, 2),
			ft_printf("%s: no such file or directory\n", infile), exit(127));
}

void	init_cmd1(t_list *lst, char *cmd1, char **envp)
{
	lst->args = ft_split(cmd1, ' ');
	if (!ft_strchr(lst->args[0], '/'))
		lst->cmd = ft_strjoin(lst->slash, lst->args[0]);
	else
		lst->cmd = lst->args[lst->absolute++];
	if (!lst->absolute)
		lst->path = find_path(envp, lst->cmd);
}

void	init_cmd2(t_list *lst, char *cmd2, char **envp)
{
	lst->args = ft_split(cmd2, ' ');
	if (!ft_strchr(lst->args[0], '/'))
		lst->cmd = ft_strjoin(lst->slash, lst->args[0]);
	else
		lst->cmd = lst->args[lst->absolute++];
	if (!lst->absolute)
		lst->path = find_path(envp, lst->cmd);
}

void	init_list(t_list **lst, char **argv, char **envp)
{
	*lst = init_nodes();
	(*lst)->next = init_nodes();
	(*lst)->next->previous = *lst;
	if ((!(*lst)->next))
		return (free_list(lst, 2), exit(1));
	init_cmd1(*lst, argv[2], envp);
	init_files(*lst, argv[1], argv[4]);
	init_cmd2((*lst)->next, argv[3], envp);
}
