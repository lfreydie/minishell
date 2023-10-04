/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blandineberthod <blandineberthod@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:42:55 by lefreydier        #+#    #+#             */
/*   Updated: 2023/10/04 15:51:28 by blandineber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
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
# include <stdbool.h>

# define MAX_INPUT_LENGTH 1024
# define MAX_TOKENS 100

// typedef struct s_bin{
// 	void			*obj;
// 	t_bin			next;
// }					t_bin;

// typedef struct s_env{
// 	char			*name;
// 	char			*value;
// 	t_env			*next;
// }					t_env;

typedef struct s_tok{
	int				id; // id cmd
	char			**cmd; // cmd "echo" "-n" "ldvbnkvjbej"
	bool			built_in; // exec ou ft
	pid_t			pid; // don't touch yet
	char			*redir_in; // file before <
	bool			heredoc;
	bool			append;
	char			*redir_out; // file after >
	struct s_tok	*next; // lst chaine, next cmd : delimiteur '|'
	struct s_tok	*previous;
}					t_tok;

typedef struct s_temp{
	char	**tokens;
	int		*redir;
}				t_temp;

typedef struct s_data{
	t_temp			*temp;
	t_tok			*head;
	//t_env			*env;
	int				num_tokens;
	int				pipefd[2];
	int				tmp_fdin;
	//t_bin			garbage;
}					t_data;

//-----------BUILT_IN_COMMANDS----------
void	ft_pwd(void);
void	ft_echo(char **args);
void	ft_cd(char **args);

//----------------INIT_FREE-------------
void	clear_tokens(t_data *data);
void	init_data(t_data *data);
void	free_all(t_data *data);

//----------------MAIN------------------
void	tokenise_input(char *input, t_data *data);
int		is_special_char(char c);

//--------------READ_LINE---------------
char	*get_prompt(void);
char	*ft_readline(void);

//---------------PARSING----------------
void	one_redirection(t_data *data, t_tok *new_token);
void	multiple_redirections(t_data *data, t_tok *new_token);
int		search_redirections(t_data *data, char *token);
void	parse_token(t_data *data);

//--------------TOKEN_UTILS-----------------
t_tok	*create_token(void);
void	add_token(t_data *data, t_tok *token);
void	print_tokens(t_data *data);
void	print_tokens1(t_data *data);

#endif
