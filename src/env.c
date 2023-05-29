/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantivi <csantivi@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 23:35:51 by csantivi          #+#    #+#             */
/*   Updated: 2023/05/28 01:38:51 by csantivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(t_list *my_env, char *str)
{
	t_env	*env;

	while (my_env)
	{
		env = my_env->content;
		if (!ft_strcmp(env->key, str))
			return (env->value);
		my_env = my_env->next;
	}
	return (NULL);
}

void	print_env(void *content)
{
	t_env	*env;

	env = (t_env*) content;
	printf("%s=%s\n", env->key, env->value);
}

t_list	*init_env(char **envp)
{
	t_list	*my_env;
	t_env	*env;
	char	**key_n_value;
	int		i;

	i = 0;
	my_env = NULL;
	while(envp[i])
	{
		key_n_value = ft_split(envp[i], '=');
		env = malloc(sizeof(t_env));
		env->key = key_n_value[0];
		env->value = key_n_value[1];
		ft_lstadd_back(&my_env, ft_lstnew((void *) env));
		free(key_n_value);
		i++;
	}
	return (my_env);
}