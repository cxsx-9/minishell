/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantivi <csantivi@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 22:47:14 by csantivi          #+#    #+#             */
/*   Updated: 2023/06/14 14:03:13 by csantivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_all_wh(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!((s[i] >= 9 && s[i] <= 13) || s[i] == 32))
			return (0);
		i++;
	}
	return (1);
}

int	check_special(char *str)
{
	int		i;
	int		q;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			q = str[i];
			i++;
			while (str[i] && str[i] != q)
				i++;
			if (!str[i])
				return (1);
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
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '?'))
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

	if (s[i] == '$')
		i++;
	len = varlen(s, i);
	if (!len)
		*new = ft_strjoin_premium(*new, "$\0", 1);
	else if (s[i] == '?')
		*new = ft_strjoin_premium(*new, value = ft_itoa(d->exit_status), 3);
	else
	{
		var_name = ft_substr(s, i, len);
		value = ft_getenv(d->env, var_name);
		if (!value)
			value = "\0";
		free(var_name);
		*new = ft_strjoin_premium(*new, value, 1);
	}
	return (len + 1);
}

int	lexer(t_d *d)
{
	d->tkn = NULL;
	if (check_special(d->buf))
		return (0);
	split_to_list(d, 0, 0);
	split_metachar(d, 0, 0, 0);
	if (check_error_arrange(d))
		return (0);
	parser(d);
	join_cmd(d);
	return (1);
}
