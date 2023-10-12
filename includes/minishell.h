/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefreydier <lefreydier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:42:55 by lefreydier        #+#    #+#             */
/*   Updated: 2023/10/12 14:51:11 by lefreydier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
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

# define ERROR 1
# define SUCCESS 0
# define READ 0
# define WRITE 1
# define ERR "Error"
# define ERR_ARG "Invalid number of arguments"
# define ERR_CMD "Command not found"
# define ERR_PIP "Pipe didn't work"
# define ERR_MAL "Malloc didn't work"
# define ERR_ENV "Environnement error"
# define ERR_NOP "The file doesn't open or isn't a file"

typedef struct s_bin{
	void			*obj;
	struct s_bin	*next;
}					t_bin;

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
	char	**tab_cmd;
	int		*redir;
}				t_temp;

typedef struct s_data{
	int				exit_flag;
	t_temp			*temp;
	t_tok			*head;
	//t_env			*env;
	char			**env;
	int				num_tokens;
	t_bin			*garbage;
}					t_data;

//----------------INIT_FREE-------------
void	clear_tokens(t_data *data);
void	free_all(t_data *data);

//----------------MAIN------------------
void	tokenise_input(char *input, t_data *data);
int		is_special_char(char c);

//--------------READ_LINE---------------
char	*get_prompt(void);
char	*ft_readline(void);

//---------------HEREDOC----------------
void	heredoc_set(t_tok *token, char *limiter);
void	heredoc_write(t_tok *token, char *limiter, int fd);

//---------------PARSING----------------
void	parse_redir_in(char **tab, t_tok *new_token);
void	parse_redir_out(char **tab, t_tok *new_token);
void	parse_cmd(char **tab, t_tok *new_token);
void	parse_token(t_data *data);

//--------------TOKEN_UTILS-----------------
t_tok	*create_token(void);
void	add_token(t_data *data, t_tok *token);
void	print_tokens(t_data *data);
void	print_tokens1(t_data *data);

#endif
