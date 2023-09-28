/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberthod <bberthod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:42:55 by lefreydier        #+#    #+#             */
/*   Updated: 2023/09/28 14:55:16 by bberthod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <sys/ioctl.h>
# include <stdlib.h>
# include <termios.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <signal.h>
# include "libft.h"
# include <stdbool.h>

# define MAX_INPUT_LENGTH 1024
# define MAX_TOKENS 100

typedef struct s_tok{
	int				id; // id cmd
	char			**cmd; // cmd "echo" "-n" "ldvbnkvjbej"
	char			**env; // ? : env pour chaque cmd
	bool			built_in; // exec ou ft
	pid_t			pid; // don't touch yet
	char			*redir_in; // file before <
	char			*redir_out; // file after >
	struct s_tok	*next; // lst chaine, next cmd : delimiteur '|'
}					t_tok;

typedef struct s_data{
	t_tok			*head;
	char			*tokens[MAX_TOKENS];
	int				num_tokens;
}					t_data;

//-----------BUILT_IN_COMMANDS----------
void	ft_pwd(void);
void	ft_echo(char **args);
void	ft_cd(char **args);

//----------------MAIN------------------
void	print_prompt(void);
void	tokenise_input(char *input, t_data *data);
int		is_special_char(char c);
void	clear_tokens(t_data *data);

//---------------PARSING----------------
void	parse_token(t_data *data);
void	add_token(t_data *data, t_tok *token);
t_tok	*create_token(int id, char **cmd, char *redir_in, char *redir_out);

//----------------UTILS-----------------
char	*ft_strtok(char *str, const char *delimiters);
void	print_tokens(t_data *data);
void	print_tokens1(t_data *data);

#endif
