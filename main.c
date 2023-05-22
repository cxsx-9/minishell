/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantivi <csantivi@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 20:22:02 by csantivi          #+#    #+#             */
/*   Updated: 2023/05/22 18:18:32 by csantivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line(); // move readline to a new line
		rl_replace_line("", 0); // clear the current input
    	rl_redisplay(); // redisplay the prompt
	}
	else if (sig == SIGTSTP || sig == SIGQUIT)
		return;
}

void	setup_signal(void)
{
	struct sigaction s_int;
	struct sigaction s_quit;
	struct sigaction s_tstp;

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

// char *ft_strtok(char *str, char *delim)
// {

// }

// void	lexer(char *input)
// {
// 	char	*token;
// 	token = ft_strtok(input, " ");
// }

void	test_ls()
{
	const char* d_path;
	DIR* directory;
	struct dirent* entry;

	d_path = ".";
	directory = opendir(d_path);
	if (directory == NULL)
	{
		perror("Error opening directory");
		return ;
	}
	while ((entry = readdir(directory)) != NULL)
	{
		printf("%s\n", entry->d_name);
	}
	closedir(directory);
}

void	test_read(char *input)
{
	int len;

	len = ft_strlen(input);
	if (ft_strncmp(input, "ls", len) == 0)
	{
		printf("it is 'ls'\n");
		test_ls();
	}
}

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
			test_read(buf);
		}
	}
	free(buf);
}
