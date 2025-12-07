/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_related.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mai <mai@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 08:23:46 by bbouarab          #+#    #+#             */
/*   Updated: 2025/12/07 13:38:52 by mai              ###   ########.fr       */
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

void create_list(t_list **lst, int cmd_total)
{
	t_list *head_ptr;
	int i;
	*lst = init_nodes();
	head_ptr = *lst;
	i = 1;
	while (i < cmd_total)
	{
		(*lst)->next = init_nodes();
		*lst = (*lst)->next;
		i++;
	}
	*lst = head_ptr;
}
size_t argvlen(char **argv)
{
	size_t size_of_argv;

	size_of_argv = 0;
	while (argv[size_of_argv])
		size_of_argv++;
	return (size_of_argv);
}
void init_cmd(t_list *lst, char **argv, char **envp)
{
	int current_cmd;
	size_t size_of_argv;

	current_cmd = 2;
	size_of_argv = argvlen(argv);
	while (lst)
	{
		lst->args = ft_split(argv[current_cmd], ' ');
		if (!ft_strchr(lst->args[0], '/'))
			lst->cmd = ft_strjoin(lst->slash, lst->args[0]);
		else
			lst->cmd = lst->args[lst->absolute++];
		if (!lst->absolute)
			lst->path = find_path(envp, lst->cmd);
		if (current_cmd == 2)
			init_files(lst, argv[1], argv[size_of_argv - 1]);
		current_cmd++;
		lst = lst->next;
	}
}

void	init_list(t_list **lst, char **argv, char **envp, int cmd_total)
{
	create_list(lst, cmd_total);
	init_cmd(*lst, argv, envp);
}
