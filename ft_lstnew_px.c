/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_px.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 08:23:46 by bbouarab          #+#    #+#             */
/*   Updated: 2025/12/03 16:00:14 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

t_list *init_nodes()
{
	t_list	*new_list;

	new_list = malloc(sizeof(t_list));
	if (!new_list)
		return (NULL);

	new_list->cmd = NULL;
	new_list->args = NULL;
	new_list->path = NULL;
	new_list->slash = "/";
	new_list->infile = 0;
	new_list->outfile = 0;
	new_list->absolute = 0;
	new_list->next = NULL;
	new_list->previous = NULL;
	return new_list;
}

void init_cmd1(t_list *lst, char *infile, char *cmd1, char *outfile, char **envp)
{
	if (!cmd1[0])
		return (free_list(&lst, 2), exit(1));
	lst->args = ft_split(cmd1, ' ');
	if (!(*lst->args))
		return (ft_printf("command not found %s\n", cmd1), free_list(&lst, 2), exit(127));
	if (!strchr(lst->args[0], '/'))
		lst->cmd = ft_strjoin(lst->slash, lst->args[0]);
	else
		lst->cmd = lst->args[lst->absolute++];
	if (!lst->absolute)
		lst->path = find_path(envp, lst->cmd);
	lst->infile = open(infile, O_RDONLY);
	lst->outfile = open(outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (lst->infile < 0 || lst->outfile < 0)
		return (free_list(&lst, 2), ft_printf("no such file or directory: %s\n", cmd1), exit(127));
	if (access(outfile, R_OK | W_OK) < 0 || access(infile, R_OK) < 0)
		return (free_list(&lst, 2), ft_printf("permission denied\n"), exit(0));
}

void init_cmd2(t_list *lst, char *cmd2, char **envp)
{
	if (!cmd2[0])
		return (free_list(&(lst->previous), 2), exit(1));
	lst->args = ft_split(cmd2, ' ');
	if (!(*lst->args))
		return (ft_printf("command not found: %s\n", cmd2), free_list(&(lst->previous), 2), exit(127));
	if (!strchr(lst->args[0], '/'))
		lst->cmd = ft_strjoin(lst->slash, lst->args[0]);
	else
		lst->cmd = lst->args[lst->absolute++];
	if (!lst->absolute)
		lst->path = find_path(envp, lst->cmd);
}

void init_list(t_list **lst, char **argv, char **envp)
{
	*lst = init_nodes();
	if (!*lst)
		exit(1);
	(*lst)->next = init_nodes();
	(*lst)->next->previous = *lst;
	if ((!(*lst)->next))
		return (free_list(lst, 1), exit(1));
	init_cmd1(*lst, argv[1], argv[2], argv[4], envp);
	init_cmd2((*lst)->next, argv[3], envp);
}
