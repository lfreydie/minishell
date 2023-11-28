/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:42:55 by lefreydier        #+#    #+#             */
/*   Updated: 2023/11/28 20:23:54 by lfreydie         ###   ########.fr       */
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
# define BACKSLASH		'\\'

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
	char			*redir;
	t_op			op;
	struct s_red	*next;
}	t_red;

typedef struct s_cmd{
	int				id;
	char			**cmd_value;
	bool			built_in;
	pid_t			pid;
	t_red			*io_red;
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
	t_list			*garbage;
	int				exit_flag;
}	t_data;

//-----------------sig------------------
void	interrupt_handler(int signum);
void	sig_init(void);
//--------------read_line---------------
char	*get_prompt(void);
char	*ft_readline(void);

//-----------------INIT-----------------

//------------INIT_PROGRAMME------------
//--------------init_prog---------------
void	init_prog(t_data *data);
void	init_grammar(t_data *data);
//---------------init_env---------------
void	new_env(t_data *data);
void	copy_env(t_data *data);
void	init_env(t_data *data);

//-------------INIT_PROCESS-------------
//-------------init_process-------------
void	init_process(t_data *data, char *input);
//----------------token-----------------
t_tok	*new_token(void);
t_tok	*add_token(t_tok **lst_tk, t_tok *new_tk);
char	*get_word_value(t_data *data, char *ptr);
void	token_data(t_data *data, char *ptr, t_tok *tk, char **grammar);
void	tokenize_input(t_data *data);
//--------------init_utils--------------
void	print_token(t_data *data);
int		ft_streq(char *str1, char *str2);
void	create_close(char *file, int flag, int mode);
void	print_cmd_list(t_data *data);
void	print_data(t_data *data);
//----------------parse-----------------
void	parse_token(t_data *data);
//----------------syntax----------------
void	check_syntax(t_data *data, t_tok *tk, t_tok *prev_tk);
//-------------INIT_PROCESS-------------
//----------------EXPAND----------------
//----------------expand----------------
t_tok	*expand(t_data *data, t_tok *tk, t_tok *prev_tk);
int		expand_quote(t_data *data, t_tok *tk, int start);
t_tok	*expand_var(t_data *data, t_tok *tk, t_tok *prev_tk, int i);
//----------expand_string_utils---------
char	*rrange_str_join(char *s1, char *s2);
char	*expand_value(t_data *data, char *var, char *ptr, int i);
char	*rrange_str(t_tok *tk, int start, int end_q);
//-------------expand_utils-------------
int		ft_isspace(char c);
int		count_word(char *ptr);
char	*find_var(char *ptr);
int		find_var_len(char *ptr);
//-----------expand_var_utils-----------
char	**word_split(char *ptr);
char	*expand_env_val(t_data *data, char *var);
t_tok	*manage_ws(char **ws, t_tok *tk, char *var, int start);
//-------------REDIRECTION--------------
//----------------redir-----------------
t_red	*lstadd_red(t_cmd *cmd);
void	add_red(t_red *red, t_tok *tk);
//---------------heredoc----------------
void	heredoc_write(t_data *data, char *limiter, int fd, char *filename);
void	heredoc_set(t_data *data, t_cmd *cmd, t_tok *tk, char *limiter);

//-----------------EXIT-----------------
//-----------garbage_collector----------
void	*gc(void *ptr);
void	rm_node(void *ptr);
void	gc_collect(void);
void	gc_collect_part(t_data *data);
//-------garbage_collector_utils--------
t_list	**_get_garbage(void);
int		ft_ptreq(char **tab, void *ptr);
//-----------------exit-----------------



#endif
