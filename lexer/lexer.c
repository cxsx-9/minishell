/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantivi <csantivi@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 22:47:14 by csantivi          #+#    #+#             */
/*   Updated: 2023/05/26 13:49:53 by csantivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_2d(char **input)
{
	int	i;

	i = 0;
	while (input[i])
		free(input[i++]);
	free(input);
}

void	show_2d(char **input)
{
	int	i;

	i = 0;
	while (input[i])
		printf("%s-", input[i++]);
	printf("\n");
}

void    scaning(char *str)
{
    int i;
    
    i = -1;
    while (str[++i])
        str[i] = ft_toupper(str[i]);
}

void	lexer(char *input)
{
	char	**datastring;
	int		i;

	i = 0;
    scaning(input);
	datastring = smart_split(input, ' ');
    if (datastring)
    {
	    show_2d(datastring);
	    free_2d(datastring);
    }
}