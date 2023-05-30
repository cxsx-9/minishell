/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantivi <csantivi@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 22:47:14 by csantivi          #+#    #+#             */
/*   Updated: 2023/05/30 18:14:42 by csantivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_special(char *str)
{
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

void	remove_quote(char *str, char q)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != q)
		{
			str[j] = str[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
}

void	clear_quote_replace(char **data, t_list *my_env)
{
	int	i;
	int	j;
	int	q;

	i = 0;
	q = 0;
	while (*data)
	{
		if (*data[0] == 39)
			remove_quote(*data, 39);
		else
		{
			if (*data[0] == 34)
				remove_quote(*data, 34);
			// replace $
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
	show_2d(d->data);
	if (!d->data)
		return ;
	clear_quote_replace(d->data, d->env);
}
