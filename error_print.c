/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 16:17:09 by bbouarab          #+#    #+#             */
/*   Updated: 2025/12/04 16:24:31 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void	command_not_found(char *cmd, char *argv)
{
	char	*merge;
	char	*merge2;
	char	*command_n_find;

	command_n_find = "command not found: ";
	if (cmd)
	{
		merge = ft_strjoin(command_n_find, cmd);
		merge2 = ft_strjoin(merge, "\n");
		free(merge);
		ft_printf("%s", merge2);
		free(merge2);
	}
	else
	{
		merge = ft_strjoin(command_n_find, argv);
		merge2 = ft_strjoin(merge, "\n");
		free(merge);
		ft_printf("%s", merge2);
		free(merge2);
	}
}

void	file_or_directory(char *directory, char *argv)
{
	char	*merge;
	char	*merge2;
	char	*command_n_find;

	command_n_find = "No such file or directory: ";
	if (directory)
	{
		merge = ft_strjoin(command_n_find, directory);
		merge2 = ft_strjoin(merge, "\n");
		free(merge);
		ft_printf("%s", merge2);
		free(merge2);
	}
	else
	{
		merge = ft_strjoin(command_n_find, argv);
		merge2 = ft_strjoin(merge, "\n");
		free(merge);
		ft_printf("%s", merge2);
		free(merge2);
	}
}
