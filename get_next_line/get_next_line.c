/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantivi <csantivi@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 22:17:52 by csantivi          #+#    #+#             */
/*   Updated: 2022/03/21 18:30:24 by csantivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_and_collect(int fd, char *current)
{
	char	*buff;
	int		readed;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	readed = 1;
	while (!found_newline(current) && readed != 0)
	{
		readed = read(fd, buff, BUFFER_SIZE);
		if (readed == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[readed] = '\0';
		current = collect(current, buff);
	}
	free(buff);
	return (current);
}

char	*get_next_line(int fd)
{
	static char	*current;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	current = read_and_collect(fd, current);
	if (!current)
		return (NULL);
	line = get_line(current);
	current = new_current(current);
	return (line);
}
