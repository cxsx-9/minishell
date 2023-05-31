/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantivi <csantivi@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 22:47:14 by csantivi          #+#    #+#             */
/*   Updated: 2023/06/01 01:36:51 by csantivi         ###   ########.fr       */
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
		if (str[i] == '\'' || str[i] == '\"')
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
	// int	i;
	// int	j;
	// int	q;
	(void)my_env;
	// i = 0;
	// q = 0;
	while (*data)
	{
		if (*data[0] == 39)
			remove_quote(*data, 39);
		else
		{
			if (*data[0] == 34)
				remove_quote(*data, 34);
		}
		data++;
	}
}

void	lexer(t_d *d)
{
	d->data = NULL;
	if (!check_special(d->buf))
		return ;
	d->data = smart_split(d->buf);
	split_to_list(d);
	ft_lstiter(d->tkn, print_tkn); // <---- print all in 't_list tkn (token)'
	// split_metachar(d); 
	// show_2d(d->data); // <---- uncomment for show
	d->data = NULL; // <--- comment for use after lexer
	if (!d->data)
		return ;
	clear_quote_replace(d->data, d->env);
}
