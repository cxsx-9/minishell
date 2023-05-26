/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantivi <csantivi@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 20:22:02 by csantivi          #+#    #+#             */
/*   Updated: 2023/05/26 12:14:40 by csantivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGTSTP || sig == SIGQUIT)
		return ;
}

void	setup_signal(void)
{
	struct sigaction	s_int;
	struct sigaction	s_quit;
	struct sigaction	s_tstp;

	s_int.sa_handler = handler;
	sigemptyset(&s_int.sa_mask);
	s_int.sa_flags = 0;
	s_quit.sa_handler = SIG_IGN;
	sigemptyset(&s_quit.sa_mask);
	s_quit.sa_flags = 0;
	s_tstp.sa_handler = SIG_IGN;
	sigemptyset(&s_tstp.sa_mask);
	s_tstp.sa_flags = 0;
	sigaction(SIGINT, &s_int, NULL);
	sigaction(SIGTSTP, &s_quit, NULL);
	sigaction(SIGQUIT, &s_tstp, NULL);
}

/*
void	init_list(t_list *node)
{
	node = (t_list*)malloc(sizeof(node));
	node->next = NULL;
	ndoe->prev = NULL;
}

t_list	*lexer(char *input)
{

	t_list	*new_node;
	t_list	*tail;
	t_list	*head;
	char	**data_string;
	int		count;
	
	//simple split into linked-list
	count = 0;
	data_string = ft_split(input, " ");
	
	while (data_string[count] != NULL)
	{
		new_node = malloc(sizeof(t_list));
		new_node->type = NULL;
		new_node->content = ft_strdup(data_string[count]);
		new_node->next = NULL;
		if (new_node->head == NULL)
		{
			head = new_node;
			tail = new_node;
		}
		else
		{
			tail->next = new_node;
			tail = new_node;
		}
		count++;
	}
	free(data_string);
	return head;
}

void show_data(t_list* head) {
    t_list* current = head;
    int count;

	count = 1;

    while (current != NULL) {
        printf("Token %d: Type: %s, Content: %s\n", count, current->type, current->content);
        current = current->next;
        count++;
    }
}

void	free_token(t_list *head)
{
	t_list* current;

	current = head;
	while(current != NULL)
	{
		t_list* tmp;
		tmp = current;
		current = current->next;
		free(tmp->content);
		free(tmp);
	}
}
*/

int	main(void)
{
	char		*buf;
	int			run;

	setup_signal();
	printf("%s>> Start ENGINE!\n%s", KRED, NONE);
	run = 1;
	while (run)
	{
		buf = readline(KGRN "csantivi \% " NONE);
		if (!buf)
		{
			printf("%s>> EOF ;-;\n%s", KRED, NONE);
			run = 0;
		}
		else if (buf[0] != '\0')
		{
			add_history(buf);
			lexer(buf);
		}
	}
	rl_clear_history();
	free(buf);
}
