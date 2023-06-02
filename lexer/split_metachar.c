/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_metachar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantivi <csantivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:39:54 by csantivi          #+#    #+#             */
/*   Updated: 2023/06/02 21:42:32 by csantivi         ###   ########.fr       */
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

void	case_cut_list(t_token **h, t_token *p, int i, int pos)
{
	int				size;
	int				redi;
	t_token			*last;
	enum e_token	type;

	size = ft_strlen(p->str);
	type = check_type(p->str[i]);
	if (i != 0)
		redi = i;
	else
	{
		if (p->str[0] == p->str[1])
			redi = 2;
		else
			redi = 1;
	}
	lst_insert(h, lst_new(ft_substr(p->str, 0, redi), type), pos);
	last = lst_new(ft_substr(p->str, redi, size - redi), type);
	lst_insert(h, last, pos + 1);
	last->next = p->next;
	lst_delone(p);
}

void	split_metachar(t_d *d)
{
	t_token	*ptr;
	int		pos;
	int		i;

	pos = 0;
	ptr = d->tkn;
	while (ptr)
	{
		i = -1;
		while (ptr->str[++i])
		{
			if (is_meta(ptr->str[i]))
			{
				if (!(ft_strlen(ptr->str) == 1 || ((ft_strlen(ptr->str) == 2)
							&& ptr->str[0] == ptr->str[1])))
				{
					case_cut_list(&d->tkn, ptr, i, pos);
					ptr = d->tkn;
					pos = 0;
					break ;
				}
			}
		}
		ptr = ptr->next;
		pos++;
	}
	lst_iter(d->tkn, print_tkn);
	printf("\n");
}
