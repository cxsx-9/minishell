/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantivi <csantivi@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:47:24 by csantivi          #+#    #+#             */
/*   Updated: 2022/03/21 18:33:05 by csantivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*read_and_collect(int fd, char *current);
int		found_newline(char *current);
size_t	ft_strlen(const char *s);
char	*collect(char *current, char *buff);
char	*get_line(char *current);
char	*new_current(char *current);

#endif
