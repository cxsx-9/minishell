/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantivi <csantivi@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 20:22:02 by csantivi          #+#    #+#             */
/*   Updated: 2023/05/29 12:19:19 by csantivi         ###   ########.fr       */
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

void	set_control_c(void)
{
	struct termios	attributes;

	tcgetattr(STDIN_FILENO, &attributes);
	attributes.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDOUT_FILENO, TCSANOW, &attributes);
}

void	setup_signal(void)
{
	struct sigaction	s_int;
	struct sigaction	s_quit;
	struct sigaction	s_tstp;

	set_control_c();
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

int	main(int ac, char **av, char **envp)
{
	t_d		*d;
	int		program;
	int		run;

	ac = (int) ac;
	av = (char **) av;
	d->envp = envp;
	d->env= init_env(envp);
	setup_signal();
	printf("%s>> Start ENGINE!\n%s", KRED, NONE);
	run = 1;
	while (run)
	{
		d->buf = readline(KGRN "csantivi \% " NONE);
		if (!d->buf)
		{
			printf("%s>> EOF ;-;\n%s", KRED, NONE);
			run = 0;
		}
		else if (ft_strlen(d->buf))
		{
			add_history(d->buf);
			// d->data = lexer(buf, d->env);
			lexer(d); // done 
			// execute_from_path(d->data, envp, d->env);
			execute_from_path(d); // done
			free_2d(d->data);
		}
	}
	ft_lstclear(&d->env, free_env);
	rl_clear_history();
	free(d->buf);
}

// int	main(int ac, char **av, char **envp)
// {
// 	char	*buf;
// 	char	**data;
// 	int		run;
// 	t_list	*my_env;

// 	ac = (int) ac;
// 	av = (char **) av;
// 	my_env = init_env(envp); 
// 	setup_signal();
// 	set_control_c();
// 	printf("%s>> Start ENGINE!\n%s", KRED, NONE);
// 	run = 1;
// 	while (run)
// 	{
// 		buf = readline(KGRN "csantivi \% " NONE);
// 		if (!buf)
// 		{
// 			printf("%s>> EOF ;-;\n%s", KRED, NONE);
// 			run = 0;
// 		}
// 		else if (ft_strlen(buf) != '\0')
// 		{
// 			add_history(buf);
// 			data = lexer(buf, my_env);
// 			execute_from_path(data, envp, my_env);
// 			free_2d(data);
// 		}
// 	}
// 	ft_lstclear(&my_env, free_env);
// 	rl_clear_history();
// 	free(buf);
// }
