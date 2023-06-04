/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantivi <csantivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 00:19:03 by csantivi          #+#    #+#             */
/*   Updated: 2023/06/05 00:44:52 by csantivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_quote(char *s, int i)
{
	int	q;
	int	start;

	start = i;
	q = s[i];
	i++;
	while (s[i] && s[i] != q)
		i++;
	if (!s[i])
		i--;
	i++;
	return (i - start);
}

char	*ft_strjoin_premium(char *s1, char *s2, int i)
{
	char	*new;

	new = ft_strjoin(s1, s2);
	if (s1 && i != 2 && i)
		free(s1);
	if (s2 && i != 1 && i)
		free(s2);
	return (new);
}

void	print_tkn(char *str)
{
	printf(" %s ->", str);
}

void	show_2d(char **input)
{
	int	i;

	if (!input || !*input)
		return ;
	i = 0;
	while (input[i])
		printf("%s,", input[i++]);
}
