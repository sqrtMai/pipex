/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 08:23:46 by bbouarab          #+#    #+#             */
/*   Updated: 2025/12/08 15:29:01 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

t_list	*init_nodes(int total_args)
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
	new_list->i = 2;
	new_list->total_args = total_args;
	new_list->next = NULL;
	new_list->previous = NULL;
	return (new_list);
}

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*temp;

	if (!lst)
		return (lst);
	temp = lst;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

void create_list(t_list **lst, int cmd_total)
{
	t_list *head_ptr;
	t_list *previous;
	int i;

	*lst = init_nodes(cmd_total);
	head_ptr = *lst;
	i = 1;
	while (i < cmd_total)
	{
		(*lst)->next = init_nodes(cmd_total);
		if (i == 1)
			previous = *lst;
		*lst = (*lst)->next;
		(*lst)->previous = previous;
		previous = previous->next;
		i++;
	}
	*lst = head_ptr;
}

void init_cmd(t_list *lst, char **argv, char **envp)
{
	int current_cmd;
	t_list *last;

	current_cmd = 2;
	while (lst)
	{
		lst->args = ft_split(argv[current_cmd], ' ');
		if (!ft_strchr(lst->args[0], '/'))
			lst->cmd = ft_strjoin(lst->slash, lst->args[0]);
		else
			lst->cmd = lst->args[lst->absolute++];
		if (!lst->absolute)
			lst->path = find_path(envp, lst->cmd);
		lst->i = current_cmd;
		if (current_cmd == 2)
			init_infile(lst, argv[1]);
		current_cmd++;
		if (!lst->next)
			last = lst;
		lst = lst->next;
	}
	init_outfile(last, argv[argvlen(argv)- 1]);
}

void	init_list(t_list **lst, char **argv, char **envp, int cmd_total)
{
	create_list(lst, cmd_total);
	init_cmd(*lst, argv, envp);
}
