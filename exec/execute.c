/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantivi <csantivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 23:30:08 by csantivi          #+#    #+#             */
/*   Updated: 2023/06/05 11:57:22 by csantivi         ###   ########.fr       */
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

void	main_execute(t_d *d)
{
	t_token	*tmp;
	int		size;

	tmp = d->tkn;
	size = lst_size(d->tkn);
	printf("It's %d command, Good luck\n", size);
	// if (size == 1)

	// if (tmp)
	// 	printf("Now I point at [%s]\n",tmp->cmd[0]);
	// else
	// 	printf("Noo It's running\n");
}
