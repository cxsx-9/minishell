/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantivi <csantivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 12:23:11 by csantivi          #+#    #+#             */
/*   Updated: 2023/06/02 21:14:09 by csantivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_2d(char **input)
{
	int	i;

	i = 0;
	if (!input)
		return ;
	while (input[i])
		free(input[i++]);
	free(input);
}

void	free_env(void *content)
{
	t_env	*env;

	env = (t_env *) content;
	free(env->key);
	free(env->value);
	free(env);
}

void	show_2d(char **input)
{
	if (!input)
		return ;
	int	i;

	i = 0;
	while (input[i])
		printf("%s,", input[i++]);
	printf("\n");
}
