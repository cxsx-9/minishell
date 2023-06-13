/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantivi <csantivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 23:30:08 by csantivi          #+#    #+#             */
/*   Updated: 2023/06/13 23:31:47 by csantivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_pipe(t_d *d, int extra)
{
	int	size;
	int	i;

	if (!extra)
	{
		d->pipe = NULL;
		return ;
	}
	d->pipe = malloc(sizeof(t_fd));
	size = (lst_size(d->tkn) - 1) * 2;
	d->pipe->size = size;
	d->pipe->pipe_fd = malloc(sizeof(int) * (size));
	i = 0;
	while (i < (size / 2))
	{
		if (pipe(d->pipe->pipe_fd + (i * 2)) < 0)
			ft_putstr_fd("Pipe : create pipe error", 2);
		i++;
	}
}

void	clear_pipe(t_fd *pipe, int extra, int freed)
{
	int	i;

	i = 0;
	if (extra)
	{
		while (i < pipe->size)
		{
			close(pipe->pipe_fd[i]);
			i++;
		}
		if (freed)
		{
			free(pipe->pipe_fd);
			free(pipe);
		}
	}
}

void	do_execute(t_d *d, t_token *cmd, int extra)
{
	int	i;

	i = 0;
	do_redirect(d, cmd);
	while (cmd)
	{
		if (!cmd->stat->is_error && cmd->token[0] != NULL)
		{
			if (extra)
				fork_exec(cmd, d, check_builtin(cmd->token), i);
			else if (!extra && check_builtin(cmd->token) == 1)
				do_builtin(cmd->token, d, 0);
			else
				fork_exec(cmd, d, check_builtin(cmd->token), -1);
		}
		i++;
		cmd = cmd->next;
	}
}

void	main_execute(t_d *d)
{
	t_token	*cmd;
	int		extra;

	cmd = d->tkn;
	extra = 0;
	if (lst_size(cmd) != 1)
		extra = 1;
	create_pipe(d, extra);
	do_here(cmd);
	do_execute(d, cmd, extra);
	clear_pipe(d->pipe, extra, 1);
}
