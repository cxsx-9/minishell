/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redi_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantivi <csantivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 01:48:45 by csantivi          #+#    #+#             */
/*   Updated: 2023/06/12 01:05:22 by csantivi         ###   ########.fr       */
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

void    do_hdoc(char *file, int id)
{
    int	fd;
	char *name;
	char *buff;

	name = ft_strjoin_premium(file, ft_itoa(id), 2);
	fd = open(name, O_WRONLY | O_APPEND | O_CREAT, 0644);
	buff = NULL;
	buff = readline("> ");
	printf("[%s][%s]\n", file, buff);
	while (ft_strcmp(file, buff)
		|| (ft_strlen(file) != ft_strlen(buff)))
	{
		buff = ft_strjoin_premium(buff, "\n", 1);
		write (fd, buff, ft_strlen(buff));
		free(buff);
		buff = readline("> ");
		printf("[%s][%s][%zu][%zu]\n", file, buff, ft_strlen(file), ft_strlen(buff));
	}
	printf("exit ;-;\n");
	if (buff)
		free(buff);
	close(fd);
}

void    do_redirect(t_token *h)
{
    t_token *cmd;
    int     i;
    int     id;

    cmd = h;
    i = 0;
    id = 0;
    while (cmd)
    {
        while (cmd->red[i])
        {
            if (check_type(cmd->red[i]) == HDOC)
                do_hdoc(cmd->red[i + 1], id);
            i += 2;
        }
		id++;
        cmd = cmd->next;
    }
}