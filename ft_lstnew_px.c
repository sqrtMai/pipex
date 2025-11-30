/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_px.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mai <mai@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 08:23:46 by bbouarab          #+#    #+#             */
/*   Updated: 2025/11/30 16:44:58 by mai              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

t_list	*ft_lstnew_px(char *argv2, char *argv3, char *infile, char *outfile, char **envp)
{
	t_list	*new_list;
	if (!argv2[0] || !argv3[0])
		exit(1);
	new_list = malloc(sizeof(t_list));
	if (!new_list)
		exit(1);
	new_list->slash = "/";
	new_list->args1 = ft_split(argv2, ' ');
	if (!(*new_list->args1))
		return free(new_list->args1), free(new_list), NULL;
	new_list->cmd1 = ft_strjoin(new_list->slash, new_list->args1[0]);
	new_list->args2 = ft_split(argv3, ' ');
	if (!(*new_list->args2))
		return (free(new_list->cmd1), free_everything(new_list->args1), free(new_list->args2), free(new_list), NULL);
	new_list->cmd2 = ft_strjoin(new_list->slash, new_list->args2[0]);



	new_list->path = find_path(envp, new_list->cmd1);
	if (!new_list->path ||check_cmd(new_list->path, new_list->cmd2))
		return (ft_printf("No command has been found"), free_list(&new_list), NULL);
	new_list->infile = open(infile, O_RDONLY);
	new_list->outfile = open(outfile, O_WRONLY | O_TRUNC | O_CREAT);
	new_list->next = NULL;
	return (new_list);
}
