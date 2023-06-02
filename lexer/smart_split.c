/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smart_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantivi <csantivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 21:46:02 by csantivi          #+#    #+#             */
/*   Updated: 2023/06/02 11:55:25 by csantivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count(char *str)
{
	int		n;
	char	c;

	n = 0;
	while (*str)
	{
		while (*str && *str == ' ')
			str++;
		if (!*str)
			break ;
		while (*str && (*str == '\'' || *str == '\"'))
		{
			c = *str++;
			while (*str && c != *str)
				str++;
			str++;
		}
		n++;
		while (*str && *str != ' ' && !(*str == '\'' || *str == '\"'))
			str++;
	}
	return (n);
}

char	*makestr(char *str, int *k)
{
	char	c;
	int		i;
	char	*tmp;

	tmp = str;
	i = 0;
	while (*str && (*str == '\'' || *str == '\"'))
	{
		c = *str++;
		while (*str && c != *str)
		{
			str++;
			i++;
		}
		str++;
		i += 2;
	}
	while (*str && *str != ' ' && !(*str == '\'' || *str == '\"'))
	{
		str++;
		i++;
	}
	*k = i;
	return (ft_strndup(tmp, i));
}

static char	**ft_split2(char *s, int n, char **str)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (i < n)
	{
		while (*s && *s == ' ')
			s++;
		str[i] = makestr(s, &k);
		s = s + k;
		i++;
	}
	str[i] = 0;
	return (str);
}

char	**smart_split(char *s)
{
	int		n;
	char	**str;

	if (!s)
		return (NULL);
	n = count(s);
	if (n == 0)
		return (NULL);
	str = (char **)malloc(sizeof(char *) * (n + 1));
	if (!str)
		return (NULL);
	return (ft_split2(s, n, str));
}
