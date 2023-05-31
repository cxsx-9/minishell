/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantivi <csantivi@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 23:39:37 by csantivi          #+#    #+#             */
/*   Updated: 2023/06/01 01:36:59 by csantivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstinsert(t_list **lst, t_list *new, int pos)
{
	// NOT YET FUNC
	t_list	*ptr;
	
	ft_putstr_fd("1 step\n", 1);
	if (!lst || !new)
		return ;
	ft_putstr_fd("2 step\n", 1);
	if (pos == 0)
	{
		ft_lstadd_front(lst, new);
		return ;
	}
	ft_putstr_fd("3 step\n", 1);
	if (pos == ft_lstsize(*lst))
	{
		ft_lstadd_back(lst, new);
		return ;
	}
	ft_putstr_fd("4 step\n", 1);
	ptr = *lst;
	while (pos)
	{
		ft_putnbr_fd(pos, 1);
		ft_putstr_fd("next-", 1);
		ptr = ptr->next;
		--pos;
	}
	ft_putstr_fd("\n", 1);
	new = ptr->next;
	ptr->next = new;
	ft_putstr_fd("DONE!!\n", 1);
}