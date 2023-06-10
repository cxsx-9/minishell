/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantivi <csantivi@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 23:30:08 by csantivi          #+#    #+#             */
/*   Updated: 2023/06/10 15:53:04 by csantivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_from_path(t_token *cmd, t_d *d)
{
	int		pid;
	char	**path;
	int		i;
	int		status;

	if (!cmd)
		return ;
	path = ft_split(ft_getenv(d->env, "PATH"), ':');
	pid = fork();
	i = -1;
	if (pid == 0)
	{
		if (is_inside('/', cmd->token[0]))
			execve(cmd->token[0], cmd->token, d->envp);
		while (path && path[++i])
		{
			path[i] = ft_strjoin(path[i], "/");
			path[i] = ft_strjoin(path[i], cmd->token[0]);
			if (!access(path[i], F_OK))
				execve(path[i], cmd->token, d->envp);
		}
		printf("bash : %s: command not found\n", cmd->token[0]);
		exit(127);
	}
	waitpid(pid, &status, 0);
	d->exit_status = WEXITSTATUS(status);
	free_2d(path);
}

void	main_execute(t_d *d)
{
	t_token	*cmd;

	cmd = d->tkn;
	while (cmd)
	{
		// if (cmd->next)
			// pipe;
		if (check_builtin(cmd->token) == 1)
		{
			printf(KBLU"Builtin func. no output\n"NONE);
			do_builtin(cmd->token, d);
		}
		else if (check_builtin(cmd->token) == 2)
		{
			printf(KBLU"Builtin func. with stdout\n"NONE);
			do_builtin(cmd->token, d);

		}
		else if (cmd->type == CMD)
			execute_from_path(cmd, d);
		cmd = cmd->next;
	}
}
