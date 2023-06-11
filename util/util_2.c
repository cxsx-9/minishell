/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantivi <csantivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 17:29:49 by csantivi          #+#    #+#             */
/*   Updated: 2023/06/11 18:16:12 by csantivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtin(char **args)
{
	if (!ft_strcmp("cd", args[0]) || !ft_strcmp("exit", args[0])
		|| !ft_strcmp("unset", args[0]) || !ft_strcmp("export", args[0])
		|| !ft_strcmp("echo", args[0]) || !ft_strcmp("pwd", args[0])
		|| !ft_strcmp("env", args[0]))
		return (1);
	return (0);
}

int	args_count(char **str)
{
	int	size;

	size = 0;
	while (str[size])
		size++;
	return (size);
}

void	show_cmd(t_token *cmd)
{
	if (!cmd)
		printf("OH Noo!! Why your list is emty!?");
	while (cmd)
	{
		show_2d(cmd->token);
		printf(" -> ");
		cmd = cmd->next;
	}
	printf("\n");
}

void	show_red(t_token *cmd)
{
	if (!cmd)
		printf("OH Noo!! Why your list is emty!?");
	while (cmd)
	{
		show_2d(cmd->red);
		printf(" -> ");
		cmd = cmd->next;
	}
	printf("\n");
}

int	is_inside(char c, char *set)
{
	while (*set)
		if (*set++ == c)
			return (1);
	return (0);
}

int	do_builtin(char **args, t_d *d, int do_fork)
{
	if (!ft_strcmp("echo", args[0]))
		ft_echo(args, d);
	else if (!ft_strcmp("cd", args[0]))
		ft_cd(args, d);
	else if (!ft_strcmp("pwd", args[0]))
		ft_pwd(d);
	else if (!ft_strcmp("export", args[0]))
		ft_export(args, d);
	else if (!ft_strcmp("unset", args[0]))
		ft_unset(args, d);
	else if (!ft_strcmp("env", args[0]))
		ft_env(d);
	else if (!ft_strcmp("exit", args[0]))
		ft_exit(args, d);
	if (do_fork)
	{
		free_for_all(d);
		exit(d->exit_status);
	}
	return (1);
}
