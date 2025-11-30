#ifndef PIPEX_H
# define PIPEX_H

#include "libft.h"
#include "ft_printf.h"
#include <errno.h>
#include <sys/wait.h>

char **ft_strstrdup(char *str);
char *find_path(char **envp, char *cmd);
void free_list(t_list **lst);

#endif
