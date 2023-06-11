/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantivi <csantivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 23:30:08 by csantivi          #+#    #+#             */
/*   Updated: 2023/06/12 02:09:29 by csantivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		{
			printf("[DO builtin]!!\n");		
			execve(path[i], token, d->envp);
		}
	}
	error_print_format_2(token[0], 1);
	free_2d(path);
	free_for_all(d);
	exit(127);
}

// void	fork_exec(char **args, t_d *d, int type)
// {
// 	int	pid;
// 	int	status;

// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		if (type == 0)
// 			execute_from_path(args, d);
// 		else if (type == 1)
// 			do_builtin(args, d, 1);
// 	}
// 	waitpid(pid, &status, 0);
// 	d->exit_status = WEXITSTATUS(status);
// }

// void	main_execute(t_d *d)
// {
// 	t_token	*cmd;
// 	int		do_fork;

// 	cmd = d->tkn;
// 	do_fork = 1;

// 	if (lst_size(cmd) == 1)
// 		do_fork = 0;
// 	do_redirect(cmd);
// 	while (cmd && cmd->token[0] != NULL)
// 	{
// 		// if (!cmd->stat->is_error)
// 		// {
// 			if (do_fork)
// 				fork_exec(cmd->token, d, check_builtin(cmd->token));
// 			else if (!do_fork && check_builtin(cmd->token))
// 				do_builtin(cmd->token, d, 0);
// 			else
// 				fork_exec(cmd->token, d, 0);
// 		// }
// 		cmd = cmd->next;
// 	}
// }


void	close_pipe(t_fd *fd)
{
	int	j;

	j = 0;
	while (j + 1 < fd->size)
	{
		close(fd->pipe[j][0]);
		close(fd->pipe[j][1]);
		j++;
	}
}

void	fork_exec(char **args, t_d *d, int type, t_fd *fd)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == 0)
	{
		if (fd->size > 1)
			dupdup(fd);
		if (type == 0)
			execute_from_path(args, d);
		else if (type == 1)
			do_builtin(args, d, 1);
	}
	waitpid(pid, &status, 0);
	// close(fd->pipe[fd->i][1]);

	if (fd->i > 0)
	{
		close(fd->pipe[fd->i - 1][0]);
	}
	d->exit_status = WEXITSTATUS(status);
}

void	free_pipe(t_fd fd)
{
	int	size;
	int	i;

	i = 0;
	size = fd.size - 1;
	while (i <= size)
	{
		free(fd.pipe[i]);
		i++;
	}
}

void	main_execute(t_d *d)
{
	t_token	*cmd;
	t_fd	fd;
	int		do_fork;

	cmd = d->tkn;
	fd.size = lst_size(cmd);
	fd.i = 0;
	do_fork = 1;
	if (lst_size(cmd) == 1)
		do_fork = 0;
	pipe_all(&fd);
	fork_fork(d, cmd, &fd, do_fork);
	free_pipe(fd);
}
