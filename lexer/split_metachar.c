/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_metachar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantivi <csantivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:39:54 by csantivi          #+#    #+#             */
/*   Updated: 2023/06/02 16:26:44 by csantivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

enum e_token	check_type(char c)
{
	if (c == '|')
		return (Pipe);
	else if (c == '<')
		return (Redi);
	else if (c == '>')
		return (Redi);
	else
		return (Idk);
}

int	is_meta(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	case_cut_list(t_token **h, t_token *p, int i, int pos)
{
	int				size;
	t_token			*last;
	enum e_token	type;

	size = ft_strlen(p->str);

	if (size == 1 || (size == 2 && i == 0
			&& p->str[0] == p->str[1]))
	{
		return (0);
	}
	else
	{
		type = check_type(p->str[i]);
		if (i != 0)
		{
			lst_insert(h, lst_new(ft_substr(p->str, 0, i), type), pos);
			last = lst_new(ft_substr(p->str, i, size - i), type);
			lst_insert(h, last, pos + 1);
			last->next = p->next;
		}
		else if (i == 0)
		{
			if (p->str[0] == p->str[1])
			{
				lst_insert(h, lst_new(ft_substr(p->str, 0, 2), type), pos);
				last = lst_new(ft_substr(p->str, 2, size - 2), type);
			}
			else
			{			
				lst_insert(h, lst_new(ft_substr(p->str, 0, 1), type), pos);
				last = lst_new(ft_substr(p->str, 1, size - 1), type);
			}
			lst_insert(h, last, pos + 1);
			last->next = p->next;
		}
		lst_delone(p);
	}
	return (1);
}

void	split_metachar(t_d *d)
{
	t_token	*ptr;
	int		pos;
	int		i;
	int		c;
	int		limit;

	pos = 0;
	ptr = d->tkn;
	limit = 0;
	while (ptr)
	{
		i = 0;
		c = 0;
		while (ptr->str[i])
		{
			if (is_meta(ptr->str[i]))
			{
				if (ft_strlen(ptr->str) == 1 || ((ft_strlen(ptr->str) == 2) && i == 0
						&& ptr->str[0] == ptr->str[1]))
				{
					i++;
					continue ;
				}
				c = case_cut_list(&d->tkn, ptr, i, pos);
				if (c)
				{
					ptr = d->tkn;
					pos = 0;
					break ;
				}
			}
			i++;
		}
		ptr = ptr->next;
		pos++;
	}
	lst_iter(d->tkn, print_tkn);
	printf("\n");
}
