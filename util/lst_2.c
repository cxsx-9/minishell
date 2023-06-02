/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantivi <csantivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:11:41 by csantivi          #+#    #+#             */
/*   Updated: 2023/06/02 13:10:20 by csantivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lst_delone(t_token *tkn)
{
	if (tkn)
	{
		free(tkn->str);
		free(tkn);
	}
}

void	lst_clear(t_token **tkn)
{
	t_token *tmp;

	if (!tkn)
		return ;
	else
	{
		while (tkn && *tkn)
		{
			tmp = (*tkn)->next;
			lst_delone(*tkn);
			*tkn = tmp;
		}
	}
}

void	lst_iter(t_token *tkn, void (*f)(char *))
{
	while (tkn)
	{
		(*f)(tkn->str);
		tkn = tkn->next;
	}
}

void	lst_insert(t_token **lst, t_token *new, int pos)
{
	t_token	*ptr;

	if (!lst || !new)
		return ;
	if (pos == 0)
	{
		lst_addfront(lst, new);
		return ;
	}
	if (pos >= lst_size(*lst))
	{
		lst_addback(lst, new);
		return ;
	}
	ptr = *lst;
	while (pos - 1)
	{
		ptr = ptr->next;
		--pos;
	}
	new->next = ptr->next;
	ptr->next = new;
}