/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantivi <csantivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:11:41 by csantivi          #+#    #+#             */
/*   Updated: 2023/06/12 19:19:54 by csantivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lst_delone(t_token *tkn)
{
	int	i;

	i = 0;
	if (tkn)
	{
		if (tkn->token)
			free_2d(tkn->token);
		// delete_file(tkn);
		while (tkn->red && tkn->red[i])
		{
			printf("[lst_2.c] POSITION [%d]\n", (i / 2));
			printf("[lst_2.c] DELO TRY [%d]\n", tkn->red_fd[i / 2]);
			if (tkn->red_fd[i / 2] != 0)
				printf("[lst_2.c] DELCLOSE [%d]\n", tkn->red_fd[i / 2]);
				close (tkn->red_fd[i / 2]);
			i += 2;
		}
		free_2d(tkn->red);
		free(tkn->red_fd);
		free(tkn->str);
		free(tkn->stat);
		free(tkn);
		printf("[lst_2.c] Finished FREE!\n");
	}
}

void	lst_clear(t_token **tkn)
{
	t_token	*tmp;

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
	*tkn = NULL;
}

void	lst_delmid(t_list *head, t_list *target)
{
	while (head && target)
	{
		if (head->next == target)
		{
			head->next = target->next;
			free_env(target->content);
			free(target);
			break ;
		}
		head = head->next;
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
