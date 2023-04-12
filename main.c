/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantivi <csantivi@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 20:22:02 by csantivi          #+#    #+#             */
/*   Updated: 2023/04/06 15:55:36 by csantivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define NONE  "\033[0m"

void	handler(int sig)
{
	
}

void	setup_signal(void)
{
	struct sigaction sa;
	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTSTP, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	/* signal interupt ctrl-c */
	// signal(SIGINT, SIG_IGN);
	/* signal terminal stop ctrl-z */
	// signal(SIGTSTP, SIG_IGN);
	/* signal quit ctrl-\ */
	// signal(SIGQUIT, SIG_IGN);
}

int	main(void)
{
	char	*buf;
	int		run;

	setup_signal();
	printf("%s>> Start ENGINE!\n%s", KRED, NONE);
	run = 1;
	while (run)
	{
		buf = readline(KGRN "csantivi \% " NONE);
		if (!buf)
		{
			printf("%s\n      EOF ;-;\n%s", KRED, NONE);
			run = 0;
		}
	}
	free(buf);
}
