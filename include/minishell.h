/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantivi <csantivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 16:15:02 by csantivi          #+#    #+#             */
/*   Updated: 2023/06/02 20:20:38 by csantivi         ###   ########.fr       */
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

enum e_token
{
	Str,
	Pipe,
	Sqt,
	Dqt,
	Redi,
	Idk
};

typedef struct	s_token
{
	char		*str;
	enum e_token	type;
	struct s_token	*next;
}			t_token;

typedef struct	s_cmd
{
	char**	cmd;
}			t_cmd;

typedef struct s_env
{
	char	*key;
	char	*value;
}			t_env;

typedef struct s_d
{
	int		exit_status;
	char	*buf;
	char	**data;
	char	**envp;
	t_list	*env;
	t_token	*tkn;
}			t_d;

// LEXER
void	lexer(t_d *d);
char	*ft_strndup(char *str, int n);

// split by space and ignore in quote
void	split_to_list(t_d *d);
char	**smart_split(char *s);
void	split_metachar(t_d *d);
void	join_cmd(t_d *d);

// EXECUTE 
void	execute_from_path(t_d *d, int i, int status);

// UNTIL
void	free_2d(char **input);
void	show_2d(char **input);
void	free_env(void *content);
t_token	*lst_new(char *str, enum e_token type);
t_token *lst_last(t_token *tkn);
void	lst_addfront(t_token **tkn, t_token *new);
void	lst_addback(t_token **tkn, t_token *new);//
int		lst_size(t_token *tkn);
void	lst_delone(t_token *tkn);
void	lst_clear(t_token **tkn);
void	lst_iter(t_token *tkn, void (*f)(char *));
void	lst_insert(t_token **lst, t_token *new, int pos);

// ENV
void	init_env(t_d *d, char **envp);
void	print_env(void *content);
void	print_tkn(char *str);
char	*ft_getenv(t_list *my_env, char *str);

#endif