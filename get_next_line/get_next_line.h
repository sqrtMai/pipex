/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:58:23 by bbouarab          #+#    #+#             */
/*   Updated: 2025/12/09 11:19:30 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

int			check_newline(char *line);
size_t		ft_strlen_new(char *c, int type);
char		*ft_strdup_gnl(char *src);
char		*ft_strdup_newline(char *new_line, char **stash, int len);
char		*get_next_line(int fd);
char		*get_next_char(int fd);
char		*fill_line(int fd, char **stash);
char		*ft_strjoin_gnl(char *s1, char *s2);

#endif
