/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantivi <csantivi@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 21:51:11 by csantivi          #+#    #+#             */
/*   Updated: 2022/03/22 14:52:05 by csantivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	found_newline(char *current)
{
	int		i;

	if (!current)
		return (0);
	i = 0;
	while (current[i])
	{
		if (current[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*collect(char *current, char *buff)
{
	int		i;
	int		j;
	char	*new;

	if (!current)
	{
		current = (char *)malloc(sizeof(char) * 1);
		current[0] = '\0';
	}
	if (!current || !buff)
		return (NULL);
	new = malloc(sizeof(char) * (ft_strlen(current) + ft_strlen(buff) + 1));
	if (!new)
		return (NULL);
	i = -1;
	j = 0;
	if (current)
		while (current[++i])
			new[i] = current[i];
	while (buff[j])
		new[i++] = buff[j++];
	new[i] = '\0';
	free(current);
	return (new);
}

char	*get_line(char *current)
{
	int		i;
	char	*new;

	i = 0;
	if (!current[i])
		return (NULL);
	while (current[i] && current[i] != '\n')
		i++;
	new = (char *)malloc(sizeof(char) * (i + 2));
	if (!new)
		return (NULL);
	i = 0;
	while (current[i])
	{
		new[i] = current[i];
		i++;
		if (current[i - 1] == '\n')
			break ;
	}
	new[i] = '\0';
	return (new);
}

char	*new_current(char *current)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	while (current[i] != '\n')
	{
		if (!current[i])
		{
			free(current);
			return (NULL);
		}
		i++;
	}
	new = (char *)malloc(sizeof(char) * (ft_strlen(current) - i + 1));
	if (!new)
		return (NULL);
	i++;
	j = 0;
	while (current[i])
		new[j++] = current[i++];
	new[j] = '\0';
	free(current);
	return (new);
}
