/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantivi <csantivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 22:47:14 by csantivi          #+#    #+#             */
/*   Updated: 2023/06/05 15:09:28 by csantivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_special(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (skip_quote(str, i) < 0)
				return (1);
			else
				i += skip_quote(str, i);
			if (!str[i])
				break ;
		}
		if (str[i] == '\\' || str[i] == ';')
			return (1);
		i++;
	}
	return (0);
}

int	varlen(char *s, int i)
{
	int	len;

	len = 0;
	while (s[i] && ft_isalnum(s[i]))
	{
		i++;
		len++;
	}
	return (len);
}

int	expand_var(char **new, char *s, int i, t_d *d)
{
	char	*var_name;
	char	*value;
	int		len;

	while (s[i] == '\'' || s[i] == '\"' || s[i] == '$')
		i++;
	len = varlen(s, i);
	if (!len)
		value = "$\0";
	else
	{
		var_name = ft_substr(s, i, len);
		value = ft_getenv(d->env, var_name);
		if (!value)
			value = "\0";
		free(var_name);
	}
	*new = ft_strjoin_premium(*new, value, 1);
	return (len + 1);
}

void	lexer(t_d *d)
{
	d->tkn = NULL;
	if (check_special(d->buf))
		return ;
	split_to_list(d, 0, 0);
	split_metachar(d, 0, 0, 0);
	parser(d);
	join_cmd(d);
}
