/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantivi <csantivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 19:29:51 by csantivi          #+#    #+#             */
/*   Updated: 2023/06/12 21:23:29 by csantivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redi_count(t_token *t, int size)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (c < size && t->str)
	{
		if (is_meta(t->str[0]) == 2)
		{
			i++;
			c++;
			t = t->next;
		}
		t = t->next;
		c++;
	}
	return (i);
}

char	**fill_cmd(t_token *runner, int size)
{
	char	**token;
	int		i;
	int		r;

	i = 0;
	r = redi_count(runner, size);
	token = malloc(sizeof(char *) * (size + 1 - (r * 2)));
	while (i < (size - (r * 2)))
	{
		if (is_meta(runner->str[0]) == 2)
			runner = runner->next->next;
		if (!runner)
			break ;
		token[i] = ft_strdup(runner->str);
		runner = runner->next;
		i++;
	}
	token[i] = 0;
	return (token);
}

char	**fill_red(t_token *runner, int size)
{
	char	**red;
	int		i;
	int		r;

	i = 0;
	r = redi_count(runner, size);
	red = malloc(sizeof(char *) * ((r * 2) + 1));
	while (i < r * 2)
	{
		if (is_meta(runner->str[0]) != 2)
		{
			runner = runner->next;
			continue ;
		}
		red[i++] = ft_strdup(runner->str);
		runner = runner->next;
		red[i] = ft_strdup(runner->str);
		runner = runner->next;
		i++;
	}
	red[i] = 0;
	return (red);
}

void	create_token(t_token **head, t_token *check, int size)
{
	t_token	*t;
	int		fd_size;
	int		i;									// comment 2

	fd_size = redi_count(check, size);
	t = lst_new(NULL, CMD);
	t->token = fill_cmd(check, size);
	t->red = fill_red(check, size);
	t->red_fd = malloc(sizeof(int *) * fd_size);	// comment
	i = 0;										// comment
	while (i < fd_size)							// comment
	{							
		t->red_fd[i] = 0;
		i++;
	}											// comment
	lst_addback(head, t);
}

void	join_cmd(t_d *d)
{
	t_token	*runner;
	t_token	*check_point;
	t_token	*head;
	int		size;

	head = NULL;
	runner = d->tkn;
	check_point = runner;
	size = 0;
	while (runner)
	{
		size++;
		if (!runner->next || runner->next->type == PIPE)
		{
			create_token(&head, check_point, size);
			size = 0;
			if (runner->next)
				runner = runner->next;
			check_point = runner->next;
		}
		runner = runner->next;
	}
	check_point = d->tkn;
	d->tkn = head;
	lst_clear(&check_point);
}








// ----- old version ------

// #include "minishell.h"

// void	fill_cmd(t_token **head, t_token *runner, int size)
// {
// 	t_token	*cmd_list;
// 	int		i;

// 	i = 0;
// 	cmd_list = lst_new(NULL, CMD);
// 	cmd_list->token = (char **)malloc(sizeof(char *) * (size + 1));
// 	while (i < size)
// 	{
// 		cmd_list->token[i] = ft_strdup(runner->str);
// 		if (runner->type != CMD)
// 			cmd_list->type = runner->type;
// 		runner = runner->next;
// 		i++;
// 	}
// 	cmd_list->token[i] = 0;
// 	lst_addback(head, cmd_list);
// }

// void	join_cmd(t_d *d)
// {
// 	t_token	*runner;
// 	t_token	*check_point;
// 	t_token	*head;
// 	int		size;

// 	head = NULL;
// 	runner = d->tkn;
// 	check_point = runner;
// 	size = 0;
// 	while (runner)
// 	{
// 		size++;
// 		if (!runner->next || runner->next->type == PIPE)
// 		{
// 			fill_cmd(&head, check_point, size);
// 			size = 0;
// 			if (runner->next)
// 				runner = runner->next;
// 			check_point = runner->next;
// 		}
// 		runner = runner->next;
// 	}
// 	check_point = d->tkn;
// 	d->tkn = head;
// 	lst_clear(&check_point);
// }