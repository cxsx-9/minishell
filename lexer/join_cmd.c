/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantivi <csantivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 19:29:51 by csantivi          #+#    #+#             */
/*   Updated: 2023/06/04 20:44:58 by csantivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_cmd(t_token **head, t_token *runner, int size)
{
	t_token	*cmd_list;
	int		i;

	i = 0;
	cmd_list = lst_new(NULL, Cmd);
	cmd_list->cmd = (char **)malloc(sizeof(char *) * (size + 1));
	while (i < size)
	{
		cmd_list->cmd[i] = ft_strdup(runner->str);
		if (runner->type == Redi)
			cmd_list->type = Redi;
		runner = runner->next;
		i++;
	}
	cmd_list->cmd[i] = 0;
	lst_addback(head, cmd_list);
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
		if (!runner->next || runner->next->type == Pipe)
		{
			fill_cmd(&head, check_point, size);
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
