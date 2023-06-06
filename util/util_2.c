/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantivi <csantivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 17:29:49 by csantivi          #+#    #+#             */
/*   Updated: 2023/06/06 18:14:26 by csantivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtin(char *str)
{
	if (!ft_strcmp("echo", str) || !ft_strcmp("cd", str)
		|| !ft_strcmp("pwd", str) || !ft_strcmp("export", str)
		|| !ft_strcmp("unset", str) || !ft_strcmp("env", str)
		|| !ft_strcmp("exit", str))
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

int	do_builtin(char **args, t_d *d)
{
	t_token	*tmp;

	tmp = d->tkn;
	if (!ft_strcmp("echo", args[0]))
		ft_echo(args, d);
	else if (!ft_strcmp("cd", args[0]))
		return (0);
	else if (!ft_strcmp("pwd", args[0]))
		ft_pwd(d);
	else if (!ft_strcmp("export", args[0]))
		ft_export(args, d);
	else if (!ft_strcmp("unset", args[0]))
		return (0);
	else if (!ft_strcmp("env", args[0]))
		ft_env(d);
	else if (!ft_strcmp("exit", args[0]))
		return (0);
	return (1);
}
