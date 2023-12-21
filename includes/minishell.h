/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:42:55 by lefreydier        #+#    #+#             */
/*   Updated: 2023/12/21 01:02:35 by lfreydie         ###   ########.fr       */
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
# include <errno.h>
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

# define SHELL "minishell"

# define FAILED -1
# define SUCCESS 0

# define TRUE 1
# define FALSE 0

# define READ 0
# define WRITE 1

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define IN 0
# define OUT 1

# define MAIN 0
# define PARENT 1
# define CHILD 2
# define HEREDOC 3
# define PARENT_H 4

# define HOMENS "HOME not set"
# define OPWDNS "OLDPWD not set"
# define ENVNS "environment not set"
# define INVOPT "invalid option"
# define ARGNB "too many arguments"
# define ERROLDPWD "error updating OLDPWD"
# define ERRPWD "error updating PWD"
# define IVALID "not a valid identifier"
# define IVALPM "invalid parameter name"
# define IVALOP "invalid option"
# define AMBRED "ambiguous redirect"

# define CD "cd"
# define EXP "export"
# define EXT "exit"
# define ENV "env"
# define PWD "pwd"
# define UST "unset"
# define ECH "echo"

# define CMDERR "command not found"
# define ISDIRE "Is a directory"
# define PERDEN "Permission denied"
# define NUMREQ "numeric argument required"
# define MALERR "malloc failed"
# define NOFLDIR "No such file or directory"

# define SYNERR "syntax error near unexpected token "
# define UNQUOTE "syntax error quote unclose "

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
	char			**value;
	int				n_args_cmd;
	bool			built_in;
	bool			launch;
	pid_t			pid;
	t_red			*io_red;
	int				fd[2];
	struct s_cmd	*next;
	struct s_cmd	*previous;
}	t_cmd;

typedef struct s_data{
	char			*line;
	t_cmd			*lst_cmd;
	t_tok			*lst_tk;
	char			**env;
	int				num_cmd;
	char			*grammar[6];
	char			*built_gram[14];
	int				tmp_fdin;
	int				pipefd[2];
	t_list			*garbage;
	int				exit;
}	t_data;

//-----------------sig------------------
void	interrupt_handler(int signum);
void	sig_init(int mode);
//--------------read_line---------------
char	*get_prompt(void);
void	ft_readline(t_data *data, char **line);

//-----------------INIT-----------------

//------------INIT_PROGRAMME------------
//--------------init_prog---------------
void	init_prog(t_data *data);
void	init_grammar(t_data *data);
void	init_built_gram(t_data *data);
//---------------init_env---------------
void	new_env(t_data *data);
void	copy_env(t_data *data);
void	init_env(t_data *data);

//-------------INIT_PROCESS-------------
//-------------init_process-------------
int		init_process(t_data *data);
//----------------token-----------------
t_tok	*new_token(void);
t_tok	*add_token(t_tok **lst_tk, t_tok *new_tk);
char	*get_word_value(t_data *data, char *ptr);
int		token_data(t_data *data, char *ptr, t_tok *tk, char **grammar);
int		tokenize_input(t_data *data);
//--------------init_utils--------------
void	print_token(t_tok *lst_tk);
int		ft_streq(char *str1, char *str2);
void	print_cmd_list(t_data *data);
void	print_gc_count(void);
//----------------parse-----------------
int		parse_token(t_data *data);
//----------------syntax----------------
int		check_syntax(t_data *data, t_tok *tk, t_tok *prev_tk);
//-------------INIT_PROCESS-------------
//----------------EXPAND----------------
//----------------expand----------------
t_tok	*expand(t_data *data, t_tok *tk, int i);
int		expand_quote(t_data *data, t_tok *tk, int start);
t_tok	*expand_var(t_data *data, t_tok *tk, int i);
int		expand_redir(t_data *data, t_red *red);
//----------expand_string_utils---------
char	*rrange_str_join(char *s1, char *s2);
char	*expand_value(t_data *data, char *var, char *ptr, int i);
char	*rrange_str(t_tok *tk, int start, int end_q);
//-------------expand_utils-------------
int		ft_isspace(char c);
int		count_word(char *ptr);
char	*find_var(char *ptr);
int		find_var_len(char *ptr);
void	manage_cmd_null(t_data *data);
//-----------expand_var_utils-----------
char	**word_split(char *ptr, int count);
char	*expand_env_val(t_data *data, char *var);
t_tok	*manage_end_ws(t_data *data, t_tok *tk, t_tok *n_tk, int end_var);
t_tok	*manage_ws(char **ws, t_tok *tk, int start);
//-------------REDIRECTION--------------
//----------------redir-----------------
t_red	*lstadd_red(t_cmd *cmd);
void	add_red(t_red *red, t_tok *tk);
int		manage_redir(t_data *data);
//---------------heredoc----------------
void	heredoc_write(t_data *data, char *limiter, t_cmd *cmd);
int		heredoc_set(t_data *data, t_cmd *cmd, char *limiter);

//-----------------EXIT-----------------
//-----------garbage_collector----------
void	*gc(void *ptr);
void	*gc_null(void *ptr);
void	free_node(void *ptr);
void	gc_collect(void);
void	gc_collect_part(t_data *data);
//-------garbage_collector_utils--------
t_list	**_get_garbage(void);
int		ft_ptreq(char **tab, void *ptr);
//-----------------exit-----------------
//-----------------error----------------
void	ft_err_syntax(t_data *data, char *shell, char *msg, char *str);
void	ft_error_msg(char *shell, char *cmd, char *arg, char *error);
void	msg_err_sys(char *msg);
void	err_sys(char *msg);

//---------------EXECUTION--------------

//----------------pipex-----------------
void	launch_exec_process(t_data *data);
void	pipex_process(t_data *data);
pid_t	fork_process(t_data *data, t_cmd *cmd);
void	exec_redir_in(t_data *data, t_cmd *cmd);
void	exec_redir_out(t_data *data, t_cmd *cmd);

//-----------------exec-----------------
char	*get_path_cmd(char *paths, char *cmd);
char	**get_paths(t_data *data);
void	execute(t_data *data, t_cmd *cmd);
void	execute_path(t_data *data, t_cmd *cmd);

//--------------exec_utils--------------
void	close_fds(int fd1, int fd2, int fd3, int fd4);
void	free_tab(char **tab);
int		ft_strcmp(const char *s1, const char *s2);

//---------------BUILT_IN---------------
//-----------built_in_process-----------
void	built_in_cmd(t_data *data, t_cmd *cmd, int fd_out);
void	built_in_parent_process(t_data *data, t_cmd *cmd);
//-------------BUILT_IN_CMD-------------
//---------------built_cd---------------
int		ft_cd(t_data *data, t_cmd *cmd, int fd_out);
//--------------built_echo--------------
int		ft_echo(t_data *data, t_cmd *cmd, int fd_out);
//--------------built_exit--------------
int		ft_exit(t_data *data, t_cmd *cmd, int fd_out);
//-------------built_utils--------------
int		ft_table_size(char **tab);
int		ft_strccmp(const char *s1, const char *s2, char c);
void	ft_clean_var(char **var);
char	*ft_var_value(char **my_env, char *target);
//--------------built_pwd---------------
int		ft_pwd(t_data *data, t_cmd *cmd, int fd_out);
//-------------built_unset--------------
int		ft_unset(t_data *data, t_cmd *cmd, int fd_out);
//--------------built_env---------------
int		ft_env(t_data *data, t_cmd *cmd, int fd_out);
//--------------env_modif---------------
void	ft_add_var(char ***env, char *var);
void	ft_del_var(char ***env, int line);
void	ft_replace_var(char ***env, char *var);
void	ft_append_var(char ***env, char *var);
//-------------built_export-------------
int		ft_export(t_data *data, t_cmd *cmd, int fd_out);
//----------built_export_utils----------
int		ft_check_arg(char *arg);
int		ft_sign_append(char *arg);
int		ft_value_is_empty(char *arg);
int		ft_var_line(char **tab, char *var);
char	*ft_var_value(char **my_env, char *target);

#endif
