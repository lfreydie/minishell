/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefreydier <lefreydier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:42:55 by lefreydier        #+#    #+#             */
/*   Updated: 2023/10/20 18:31:46 by lefreydier       ###   ########.fr       */
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

# define LESS			"<"
# define MUCH_LESS		"<<"
# define MORE			">"
# define MUCH_MORE		">>"
# define BAR			"|"
# define S_NEWLINE		"\n"
# define SINGLE_QUOTE	'\''
# define DOUBLE_QUOTE	'"'
# define METACHARACTERS	" <>|\n\t"
# define SPACE			' '

typedef struct s_bin{
	void			*obj;
	struct s_bin	*next;
}	t_bin;

typedef enum e_type{
	CTRL_OP,
	RED_OP,
	WORD
}	t_type;

typedef enum e_op{
	IN_RED,
	HEREDOC_RED,
	OUTTR_RED,
	OUTAP_RED,
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
	char			**cmd;
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
	t_bin			*garbage;
}	t_data;

//----------------INIT_FREE-------------
void	clear_tokens(t_data *data);
void	free_all(t_data *data);

//----------------MAIN------------------
void	interrupt_handler(int signum);

//--------------READ_LINE---------------
char	*get_prompt(void);
char	*ft_readline(void);

//-------------INIT_PROCESS-------------
void	init_process(t_data *data, char *input);
void	init_grammar(t_data *data);

//----------------TOKEN-----------------
t_tok	*add_token(t_data *data);
char	*get_word_value(t_data *data, char *ptr);
void	token_data(t_data *data, char *ptr, t_tok *tk, char **grammar);
void	tokenize_input(t_data *data);

//----------------TOKEN-----------------
void	print_token(t_data *data);

#endif
