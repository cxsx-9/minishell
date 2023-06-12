/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantivi <csantivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 00:08:10 by psaeyang          #+#    #+#             */
/*   Updated: 2023/06/12 04:14:09 by csantivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	dupdup(t_fd *fd)
// {
// 	if (fd->i == 0)
// 	{
// 		printf(KMAG"this is first cmd%s\n", NONE);
// 		dup2(fd->pipe[fd->i][1], STDOUT_FILENO);
// 		close_pipe(fd);
// 	}
// 	else if (fd->i == fd->size - 1)
// 	{
// 		printf(KMAG"this is last cmd%s\n", NONE);
// 		dup2(fd->pipe[fd->i - 1][0], STDIN_FILENO);
// 		close_pipe(fd);
// 	}
// 	else
// 	{
// 		printf(KMAG"this is middle cmd%s\n", NONE);
// 		dup2(fd->pipe[fd->i - 1][0], STDIN_FILENO);
// 		dup2(fd->pipe[fd->i][1], STDOUT_FILENO);
// 		close_pipe(fd);
// 	}
// }

//main exec
// void	pipe_all(t_fd *fd)
// {
// 	// printf("pipe here\n");
// 	if (fd->size != 1)
// 	{
// 		fd->pipe = malloc(sizeof(int *) * (fd->size - 1));
// 		while (fd->i + 1 < fd->size)
// 		{
// 			pipe(fd->pipe[fd->i]);
// 			fd->i++;
// 		}
// 		fd->i = 0;
// 	}
// }

// void	fork_fork(t_d *d, t_token *cmd, t_fd *fd, int do_fork)
// {
// 	while (cmd)
// 	{
// 		if (do_fork)
// 			fork_exec(cmd->token, d, check_builtin(cmd->token), fd);
// 		else if (!do_fork && check_builtin(cmd->token))
// 			do_builtin(cmd->token, d, 0);
// 		else
// 			fork_exec(cmd->token, d, 0, fd);
// 		cmd = cmd->next;
// 		fd->i++;
// 	}
// }

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