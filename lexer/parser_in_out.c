/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_in_out.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantivi <csantivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 01:48:45 by csantivi          #+#    #+#             */
/*   Updated: 2023/06/11 17:25:54 by csantivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	manage_infile(t_token *t, t_token *r)
// {
//     int fd;

//     t = (t_token* ) t;
//     r = r->next;
//     if (access(r->str, F_OK | X_OK))
//     {
//     if (access(r->str, F_OK))
//             error_print_format_2(r->str, 3);
//         else if(access(r->str, X_OK))
//             error_print_format_2(r->str, 4);
//         t->redi->is_error = 1;
//         return ;
//     }
//     t->redi->infile = open(r->str, O_RDONLY);
// }

// void	manage_infile(t_token *t, t_token *r)
// {
//     char    *line;

    
// }