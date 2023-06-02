/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantivi <csantivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 22:47:14 by csantivi          #+#    #+#             */
/*   Updated: 2023/06/02 15:34:43 by csantivi         ###   ########.fr       */
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
				return (1);
		}
		if (str[i] == '\\' || str[i] == ';')
			return (1);
		i++;
	}
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

void	test_insert(t_d *d)
{
	t_token	*new;
	t_token	*new2;

	new = malloc(sizeof(t_token));
	new2 = malloc(sizeof(t_token));
	new->str = (char *)malloc(sizeof(char) * 4);
	new2->str = (char *)malloc(sizeof(char) * 4);
	ft_strlcpy(new->str, "aaa", 4);
	ft_strlcpy(new2->str, "bbb", 4);
	new->type = Idk;
	new2->type = Idk;
	new->next = NULL;
	new2->next = NULL;
	// lst_addfront(&d->tkn, new);
	
	lst_insert(&d->tkn, new, 1);
	lst_insert(&d->tkn, new2, 1 + 1);
	lst_iter(d->tkn, print_tkn); // <---- print all in 't_list tkn (token)'
	printf("size[%d]", lst_size(d->tkn));
	printf("\n");
}

void	lexer(t_d *d)
{
	d->data = NULL;
	d->tkn = NULL;
	if (check_special(d->buf))
		return ;
	d->data = smart_split(d->buf);
	split_to_list(d);
	// test_insert(d);
	split_metachar(d);
	// show_2d(d->data); // <---- uncomment for show
	d->data = NULL; // <--- comment for use after lexer
	if (!d->data)
		return ;
	clear_quote_replace(d->data, d->env);
}
