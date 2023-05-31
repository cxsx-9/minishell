/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantivi <csantivi@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 12:23:11 by csantivi          #+#    #+#             */
/*   Updated: 2023/06/01 01:32:30 by csantivi         ###   ########.fr       */
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

void	free_tkn(void *content)
{
	t_token	*token;

	token = (t_token *) content;
	free(token->str);
	free(token);
}

void	show_2d(char **input)
{
	int	i;

	i = 0;
	while (input[i])
		printf("%s,", input[i++]);
	printf("\n");
}
