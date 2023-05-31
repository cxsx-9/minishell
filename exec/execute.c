/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantivi <csantivi@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 23:30:08 by csantivi          #+#    #+#             */
/*   Updated: 2023/06/01 01:31:35 by csantivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_from_path(t_d *d, int i, int status)
{
	int		pid;
	char	**path;

	if (!d->data)
		return ;
	path = ft_split(ft_getenv(d->env, "PATH"), ':');
	pid = fork();
	i = 0;
	if (pid == 0)
	{
		execve(d->data[0], d->data, d->envp);
		while (path[i])
		{
			path[i] = ft_strjoin(path[i], "/");
			path[i] = ft_strjoin(path[i], d->data[0]);
			execve(path[i], d->data, d->envp);
			i++;
		}
		printf("bash : %s: comand not found\n", d->data[0]);
		exit(127);
	}
	waitpid(pid, &status, 0);
	d->exit_status = WEXITSTATUS(status);
	free_2d(path);
}
