/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 16:17:20 by bbouarab          #+#    #+#             */
/*   Updated: 2025/12/10 14:28:17 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
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
	int				i;
	int				total_args;
	int				here_doc;
	pid_t			pid;
	struct s_list	*next;
	struct s_list	*previous;
}	t_list;

void	tree_of_closing(int **fds, int current_process, int total_args);
void	tree_of_process(int **fds, t_list *lst, char **argv, char **envp);
void	free_fd(int **fds, int total_args);

t_list	*ft_lstlast(t_list *lst);
char	**ft_strstrdup(char *str);
char	*find_path(char **envp, char *cmd);

void	free_fd(int **fds, int total_args);
void	free_list(t_list **lst);
int		free_and_continue(char *s);
void	free_everything(void **vector);
size_t	argvlen(char **argv);
void	init_infile(t_list *lst, char *infile);
void	init_list(t_list **lst, char **argv, char **envp, int cmd_nbr);
void	init_outfile(t_list *lst, char *outfile);
int		create_process(int **fds, t_list *lst, char **argv, char **envp);
char	*check_absolute_0(int **fds, t_list *lst, char **argv, int fd2);
char	*check_absolute_1(int **fds, t_list *lst, char **argv, int fd2);
char	*check_absolute_middle_0(int **fds, t_list *lst, char **argv);
char	*check_absolute_middle_1(int **fds, t_list *lst, char **argv);
void	close_all_pipes(int **fds, int total_args);
void	closes(int fd1, int fd2);
void	here_doc(t_list *lst, int **fds, char **argv, char **envp);
void	first_process(t_list *lst, int **fds, char **argv, char **envp);
void	middle_process(int **fds, t_list *lst, char **envp, char **argv);
void	last_process(int **fds, t_list *lst, char **envp, char **argv);

int		ft_findstr(char *str, char *searched);
int		check_cmd(char *full_path);
void	free_everything(void **str);
void	n_cmd(char *cmd, char *argv);
void	file_or_directory(char *directory, char *argv);
#endif
