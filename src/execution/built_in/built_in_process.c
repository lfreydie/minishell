/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:55:09 by lfreydie          #+#    #+#             */
/*   Updated: 2023/12/14 19:41:14 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_in_cmd(t_data *data, t_cmd *cmd, int fd_out)
{
	if (cmd->built_in == 0)
		ft_echo(data, cmd, fd_out);
	else if (cmd->built_in == 1)
		ft_cd(data, cmd, fd_out);
	else if (cmd->built_in == 2)
		ft_env(data, cmd, fd_out);
	else if (cmd->built_in == 3)
		ft_exit(data, cmd, fd_out);
	else if (cmd->built_in == 4)
		ft_export(data, cmd, fd_out);
	else if (cmd->built_in == 5)
		ft_pwd(data, cmd, fd_out);
	else if (cmd->built_in == 6)
		ft_unset(data, cmd, fd_out);
}

void	built_in_parent_process(t_data *data, t_cmd *cmd)
{
	int	fd_out;

	fd_out = STDOUT;
	if (cmd->fd[IN] > 0)
	{
		if (dup2(cmd->fd[IN], STDIN) < 0)
			perror("dup2");
		close(cmd->fd[IN]);
	}
	if (cmd->fd[OUT] > 0)
	{
		if (dup2(cmd->fd[OUT], STDOUT) < 0)
			perror("dup2");
		fd_out = cmd->fd[OUT];
		close(cmd->fd[OUT]);
	}
	built_in_cmd(data, cmd, fd_out);
}
