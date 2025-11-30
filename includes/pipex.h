#ifndef PIPEX_H
# define PIPEX_H

#include "libft.h"
#include "ft_printf.h"
#include <errno.h>
#include <sys/wait.h>

typedef struct s_list
{
	char			*cmd1;
	char			*cmd2;
	char			**args1;
	char			**args2;
	char			*path;
	char			*slash;
	int				infile;
	int				outfile;
	struct s_list	*next;
}	t_list;


char **ft_strstrdup(char *str);
char *find_path(char **envp, char *cmd);
void free_list(t_list **lst);
t_list	*ft_lstnew_px(char *argv2, char *argv3, char *infile, char *outfile, char **envp);
int check_cmd(char *path, char *cmd);
void	free_everything(char **str);
#endif
