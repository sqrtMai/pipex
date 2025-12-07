/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mai <mai@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 16:17:20 by bbouarab          #+#    #+#             */
/*   Updated: 2025/12/07 16:32:30 by mai              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include "ft_printf.h"
# include <errno.h>
# include <sys/wait.h>

typedef struct s_list
{
	char			*cmd;
	char			**args;
	char			*path;
	char			*slash;
	int				infile;
	int				outfile;
	int				absolute;
	int				index;
	int 			total_args;
	pid_t 			pid;
	struct s_list	*next;
	struct s_list	*previous;
}	t_list;

void tree_of_closing(int **fds, int current_process, int total_args);
void tree_of_process(int **fds, t_list *lst, char **argv, char **envp);
void free_fd(int **fds, int total_args);

char	**ft_strstrdup(char *str);
char	*find_path(char **envp, char *cmd);
void	free_list(t_list **lst);
void	init_list(t_list **lst, char **argv, char **envp, int cmd_nbr);
int		check_cmd(char *full_path);
void	free_everything(void **str);
void	command_not_found(char *cmd, char *argv);
void	file_or_directory(char *directory, char *argv);
#endif
