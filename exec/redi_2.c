/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redi_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantivi <csantivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:56:00 by csantivi          #+#    #+#             */
/*   Updated: 2023/06/12 23:08:17 by csantivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_outfile(char *file, int i, t_token *cmd)
{
	int	fd;

	if (!access(file, F_OK) && access(file, W_OK))
	{
		error_print_format_2(file, 4);
		cmd->stat->is_error = 1;
	}
	else
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC,  0644);
		printf("[redi_2.c] outfile [%s][%d]\n", file, fd);
		printf("[redi_2.c] save at [%d] : \n", i);
		cmd->red_fd[i] = fd;
	}
}

void	do_append(char *file, int i, t_token *cmd)
{
	int	fd;

	if (!access(file, F_OK) && access(file, W_OK))
	{
		error_print_format_2(file, 4);
		cmd->stat->is_error = 1;
	}
	else
	{
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND | O_TRUNC,  0644);
		printf("[redi_2.c] append [%s][%d]\n", file, fd);
		printf("[redi_2.c] save at [%d] : \n", i);
		cmd->red_fd[i] = fd;
	}
}

// void	set_fd()

void	setup_inout(t_token *cmd)
{
	int	i;
	int	id;

	id = 0;
	while (cmd)
	{
		i = 0;
		while (!cmd->stat->is_error && cmd->red[i])
		{
			if (check_type(cmd->red[i]) == REIN
				|| check_type(cmd->red[i]) == HDOC)
				cmd->stat->infile = cmd->red_fd[i / 2];
			else if (check_type(cmd->red[i]) == REOUT
				|| check_type(cmd->red[i]) == REAPP)
				cmd->stat->outfile = cmd->red_fd[i / 2];
			i += 2;
		}
		id++;
		cmd = cmd->next;
	}
}
