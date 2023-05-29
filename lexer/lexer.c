/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantivi <csantivi@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 22:47:14 by csantivi          #+#    #+#             */
/*   Updated: 2023/05/29 15:54:15 by csantivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_special(char *str)
{
	char	*sub;
	int		i;
	int		q;

	i = 0;
	q = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"') // find unclose quote
		{
			q = str[i];
			i++;
			while (str[i] && str[i] != q)
				i++;
			if (!str[i])
				return (0);
		}
		// if (q)
		if (str[i] == '\\' || str[i] == ';')
			return (0);
		i++;
	}
	return (1);
}

int	is_white_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || \
	c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

void	clear_qoute_replace(char **data, t_list *my_env)
{
	int	i;
	int	j;
	int	q;

	i = 0;
	q = 0;
	while (*data)
	{
		if (*data[0] == 39)
			*data = ft_strtrim(*data, "\'");
		else
		{
			if (*data[0] == 34)
				*data = ft_strtrim(*data, "\"");
			// find_and_replace(data[i], my_env);
		}
		data++;
	}
}

void	lexer(t_d *d)
{
	d->data = NULL;
	if (!check_special(d->buf))
		return ;
	d->data = smart_split(d->buf, ' ');
	if (!d->data)
		return ;
	clear_qoute_replace(d->data, d->env);
}
