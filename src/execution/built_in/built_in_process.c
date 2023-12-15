/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:55:09 by lfreydie          #+#    #+#             */
/*   Updated: 2023/12/15 17:56:38 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_in_cmd(t_data *data, t_cmd *cmd, int fd_out)
{
	if (cmd->value[0][0] == 'e')
	{
		if (cmd->value[0][1] == 'c')
			ft_echo(data, cmd, fd_out);
		else if (cmd->value[0][1] == 'n')
			ft_env(data, cmd, fd_out);
		else if (cmd->value[0][2] == 'i')
			ft_exit(data, cmd, fd_out);
		else
			ft_export(data, cmd, fd_out);
	}
	else if (cmd->value[0][0] == 'c')
		ft_cd(data, cmd, fd_out);
	else if (cmd->value[0][0] == 'p')
		ft_pwd(data, cmd, fd_out);
	else
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
