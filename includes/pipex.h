#ifndef PIPEX_H
# define PIPEX_H

#include "libft.h"
#include "ft_printf.h"
#include <errno.h>
#include <sys/wait.h>

typedef struct s_list
{
	char			*cmd;
	char			**args;
	char			*path;
	char			*slash;
	int				infile;
	int				outfile;
	int				absolute;
	struct s_list	*next;
	struct s_list	*previous;
}	t_list;


char **ft_strstrdup(char *str);
char *find_path(char **envp, char *cmd);
void free_list(t_list **lst);
void init_list(t_list **lst, char **argv, char **envp);
int check_cmd(char *path, char *cmd, int i);
void	free_everything(char **str);
#endif
