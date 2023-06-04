/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantivi <csantivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 19:29:51 by csantivi          #+#    #+#             */
/*   Updated: 2023/06/04 11:32:43 by csantivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void join_cmd(t_d *d)
// {
// 	t_token *i;
//     t_token *j;

//     int     size;

//     i = d->tkn;
//     j = i;
//     size = 0;
//     while (i)
//     {
//         if (Pipe == check_type(i->type))
//         {
//             merge_list(j, size);
//             size = 0;
//         }
//         j = i;
//         size++;
//         i = i->next;
//     }
// }