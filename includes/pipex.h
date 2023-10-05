/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefreydier <lefreydier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 13:06:33 by lfreydie          #+#    #+#             */
/*   Updated: 2023/10/05 17:59:33 by lefreydier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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

//	PIPEX
void	launch_exec_process(t_data *data);
void	pipex_process(t_exec *exec);
pid_t	fork_process(t_exec *exec);
void	exec_redir_in(t_exec *exec);
void	exec_redir_out(t_exec *exec);

//	EXEC
char	*get_path_cmd(char *paths, char *cmd);
char	**get_paths(t_pipex *infos);
void	execute(t_pipex *infos, int i);
void	execute_path(t_pipex *infos, int i);

#endif
