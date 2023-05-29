/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantivi <csantivi@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 16:15:02 by csantivi          #+#    #+#             */
/*   Updated: 2023/05/29 15:55:15 by csantivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <errno.h>
# include "../libft/libft.h"
# include <termios.h>
# include <curses.h>
# include <term.h>

# define KNRM  "\x1B[0m"
# define KRED  "\x1B[31m"
# define KGRN  "\x1B[32m"
# define KYEL  "\x1B[33m"
# define KBLU  "\x1B[34m"
# define KMAG  "\x1B[35m"
# define KCYN  "\x1B[36m"
# define KWHT  "\x1B[37m"
# define NONE  "\033[0m"

# define MAX_HISTORY 100

typedef struct s_d
{ 
	int     exit_status;
    char    *buf;
    char    **data;
    char    **envp;
	t_list	*env;
}			t_d;

typedef struct s_env
{
	char	*key;
	char	*value;	
}			t_env;

/* LEXER */
void    lexer(t_d *d);
char	**smart_split(char const *s, char c);

/* EXECUTE */
void	execute_from_path(t_d *d);

/* UNTIL */
void	free_2d(char **input);
void	show_2d(char **input);
void	free_env(void *content);

/* ENV */
t_list	*init_env(char **envp);
void	print_env(void *content);
char	*ft_getenv(t_list *my_env, char *str);

#endif