/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantivi <csantivi@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:20:12 by csantivi          #+#    #+#             */
/*   Updated: 2023/06/10 16:41:27 by csantivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	error_print(char *s1, char *s2, int type)
// {
	
// }

// int check_error_arrange(t_d *d)
// {
// 	t_token *ptr;

// 	ptr = d->tkn;
// 	if (ptr->type == PIPE)
// 		return (0);
// 	while (ptr)
// 	{
// 		if (ptr->type != CMD && (ptr->type == ptr->next->type))
// 		{
// 			write(1, ptr->next->str, ft_strlen(ptr->next->str));
// 			ft_putstr_fd("bash: syntax error near unexpected token ", 2);
// 		}
// 		ptr = ptr->next;
// 	}
// }