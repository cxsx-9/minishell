/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_in.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantivi <csantivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 22:33:07 by csantivi          #+#    #+#             */
/*   Updated: 2023/06/04 11:48:41 by csantivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_in_dq(char **new, char *s, int i)
{
	int	pos_in;
	int	start;

	pos_in = i;
	if (s[i] == '\"')
		i++;
	start = i;
	while (s[i] && s[i] != '$' && s[i] != '\"' )
		i++;
	*new = ft_strjoin_premium(*new, ft_substr(s, start, (i - start)), -1);
	return (i - pos_in);
}

int	fill_in_str(char **new, char *s, int i)
{
	int		pos_in;
	int		start;
	char	*tmp;

	pos_in = i;
	if (s[i] == '\"')
		i++;
	start = i;
	while (s[i] && s[i] != '$' && s[i] != '\'' && s[i] != '\"')
		i++;
	tmp = ft_substr(s, start, (i - start));
	*new = ft_strjoin_premium(*new, ft_substr(s, start, (i - start)), -1);
	return (i - pos_in);
}

int	fill_dquote(char **new, char *s, int i, t_d *d)
{
	int	skip;
	int	q;

	skip = skip_quote(s, i);
	q = s[i++];
	while (s[i] && s[i] != '\"')
	{
		if (s[i] == '$')
			i += expand_var(new, s, i, d);
		else
			i += fill_in_dq(new, s, i);
	}
	return (skip);
}

int	fill_string(char **new, char *s, int i, t_d *d)
{
	int	skip;

	skip = 0;
	if (s[i] == '$')
		skip += expand_var(new, s, i, d);
	else
		skip += fill_in_str(new, s, i);
	return (skip);
}

int	fill_squote(char **new, char *s, int i)
{
	int	skip;
	int	q;

	skip = skip_quote(s, i);
	q = s[i++];
	*new = ft_strjoin_premium(*new, ft_substr(s, i, skip - 2), -1);
	return (skip);
}
