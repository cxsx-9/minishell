/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_to_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantivi <csantivi@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 21:46:02 by csantivi          #+#    #+#             */
/*   Updated: 2023/06/01 00:55:14 by csantivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count(char *str)
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

static char	*ft_strndup(char *str, int n)
{
	int		i;
	char	*ret;

	i = 0;
	ret = malloc(n + 1);
	while (*str && n)
	{
		ret[i] = *str;
		str++;
		i++;
		--n;
	}
	ret[i] = 0;
	return (ret);
}

static char	*makestr(char *str, int *k)
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

void	split_to_list(t_d *d)
{
	t_token	*new_tkn;
	int		n;
	int		i;
	char	**str;

	i = 0;
	if (!d->buf)
		return ;
	n = count(d->buf);
	if (n == 0)
		return ;
	str = (char **)malloc(sizeof(char *) * (n + 1));
	if (!str)
		return ;
	str = ft_split2(d->buf, n, str);
	d->tkn = NULL;
	while (str[i])
	{
		new_tkn = malloc(sizeof(t_token));
		new_tkn->str = ft_strndup(str[i], ft_strlen(str[i]));
		new_tkn->type = Idk;
		ft_lstadd_back(&d->tkn, ft_lstnew((void *) new_tkn));
		i++;
	}
	free_2d(str);
}
