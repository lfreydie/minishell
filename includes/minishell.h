/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefreydier <lefreydier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:42:55 by lefreydier        #+#    #+#             */
/*   Updated: 2023/10/26 16:24:13 by lefreydier       ###   ########.fr       */
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

# define DEFAULT_ENV	"PATH=NULL:PWD=NULL:PS1=>:SHLVL=0:_=NULL"
# define DEFAULT_PATH	"PATH=/usr/local/sbin:\
						/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
# define ENV_SEP		':'

# define LESS			"<"
# define MUCH_LESS		"<<"
# define MORE			">"
# define MUCH_MORE		">>"
# define BAR			"|"
# define S_NEWLINE		"newline"
# define SINGLE_QUOTE	'\''
# define DOUBLE_QUOTE	'"'
# define METACHARACTERS	" <>|\n\t"
# define SPACE			' '

struct s_state
{
	volatile sig_atomic_t	signal;
}	t_state;

typedef enum e_type{
	CTRL_OP,
	RED_OP,
	WORD
}	t_type;

typedef enum e_op{
	HEREDOC_RED,
	IN_RED,
	OUTAP_RED,
	OUTTR_RED,
	PIPE,
	NWLINE,
	NONE
}	t_op;

typedef struct s_tok{
	t_type			type;
	t_op			op;
	char			*value;
	struct s_tok	*next;
}	t_tok;

typedef struct s_red{
	char			*red_in;
	bool			heredoc;
	char			*red_out;
	bool			append;
}	t_red;

typedef struct s_cmd{
	int				id;
	char			**cmd_value;
	bool			built_in;
	pid_t			pid;
	t_red			io_red;
	struct s_cmd	*next;
	struct s_cmd	*previous;
}	t_cmd;

typedef struct s_data{
	char			*line;
	t_cmd			*lst_cmd;
	t_tok			*lst_tk;
	char			**env;
	int				num_cmd;
	char			**grammar;
	int				exit_flag;
}	t_data;

//----------------INIT_FREE-------------
void	free_t_data(t_data *data);
void	free_part(t_data *data);

//-----------------SIG------------------
void	interrupt_handler(int signum);
void	sig_init(void);

//--------------READ_LINE---------------
char	*get_prompt(void);
char	*ft_readline(void);

//--------------INIT_PROG---------------
void	init_prog(t_data *data);
void	init_grammar(t_data *data);

//-------------INIT_PROCESS-------------
void	init_process(t_data *data, char *input);

//---------------INIT_ENV---------------
void	new_env(t_data *data);
void	copy_env(t_data *data);
void	init_env(t_data *data);

//----------------TOKEN-----------------
t_tok	*add_token(t_data *data);
char	*get_word_value(t_data *data, char *ptr);
void	token_data(t_data *data, char *ptr, t_tok *tk, char **grammar);
void	tokenize_input(t_data *data);

//--------------INIT_UTILS--------------
void	print_token(t_data *data);
void	create_close(char *file, int flag, int mode);
void	print_cmd_list(t_data *data);

//-------------PARSE_TOKEN--------------
void	parse_token(t_data *data);

//----------------SYNTAX----------------
void	check_syntax(t_data *data, t_tok *tk, t_tok *prev_tk);
t_tok	*expand(t_tok *tk);

//---------------HEREDOC----------------
void	heredoc_write(t_data *data, char *limiter, int fd, char *filename);
void	heredoc_set(t_data *data, t_cmd *cmd, t_tok *tk, char *limiter);

#endif
