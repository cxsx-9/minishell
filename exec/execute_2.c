/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantivi <csantivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:18:19 by csantivi          #+#    #+#             */
/*   Updated: 2023/06/14 17:22:38 by csantivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

void	execute_from_path(char **token, t_d *d)
{
	char	**path;
	int		i;

	if (!token)
		return ;
	path = ft_split(ft_getenv(d->env, "PATH"), ':');
	i = -1;
	if (is_inside('/', token[0]))
		execve(token[0], token, d->envp);
	while (path && path[++i])
	{
		path[i] = ft_strjoin_premium(path[i], "/", 1);
		path[i] = ft_strjoin_premium(path[i], token[0], 1);
		if (!access(path[i], F_OK))
			execve(path[i], token, d->envp);
	}
	error_print_format_2(token[0], 1);
	free_2d(path);
	free_for_all(d);
	exit(127);
}

void	manage_direction(t_token *cmd)
{
	dup2(cmd->stat->infile, STDIN_FILENO);
	dup2(cmd->stat->outfile, STDOUT_FILENO);
}

void	close_main_pipe(t_token *cmd, t_fd *p, int i)
{
	if (i == -1)
		return ;
	if (i == 0)
		close(p->pipe_fd[(i * 2) + 1]);
	else if (cmd->next == NULL)
		close(p->pipe_fd[(i * 2) - 2]);
	else
	{
		close(p->pipe_fd[(i * 2) - 2]);
		close(p->pipe_fd[(i * 2) + 1]);
	}
}

int	fork_exec(t_token *cmd, t_d *d, int type, int i)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		manage_direction(cmd);
		if (!type)
			execute_from_path(cmd->token, d);
		else if (type)
			do_builtin(cmd->token, d, 1);
		if (i != -1)
			clear_pipe(d->pipe, 1, 0);
	}
	close_main_pipe(cmd, d->pipe, i);
	return (pid);
}
