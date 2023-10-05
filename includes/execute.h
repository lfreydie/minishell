/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefreydier <lefreydier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 13:06:33 by lfreydie          #+#    #+#             */
/*   Updated: 2023/10/05 18:49:27 by lefreydier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"
# include <fcntl.h>
# include <errno.h>

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

typedef struct s_exec
{
	t_data	*data;
	t_tok	*token;
	int		tmp_fdin;
	int		pipefd[2];
}				t_exec;

//----------------PIPEX-----------------
void	launch_exec_process(t_data *data);
void	pipex_process(t_exec *exec);
pid_t	fork_process(t_exec *exec);
void	exec_redir_in(t_exec *exec);
void	exec_redir_out(t_exec *exec);

//-----------------EXEC-----------------
char	*get_path_cmd(char *paths, char *cmd);
char	**get_paths(t_exec *exec);
void	execute(t_exec *exec);
void	execute_path(t_exec *exec);

//-----------BUILT_IN_COMMANDS----------
void	ft_pwd(void);
void	ft_echo(char **args);
void	ft_cd(char **args);
void	ft_export(char **args);
void	ft_unset(char **args);
void	ft_env(char **args);
void	ft_exit(void);

//-----------BUILT_IN_PROCESS-----------
void	find_built_in_cmd(t_exec *exec);
pid_t	built_in_child_process(t_exec *exec);
void	built_in_parent_process(t_exec *exec);

#endif
