/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:55:09 by lfreydie          #+#    #+#             */
/*   Updated: 2023/12/21 00:42:17 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_in_cmd(t_data *data, t_cmd *cmd, int fd_out)
{
	if (cmd->value[0][0] == 'e')
	{
		if (cmd->value[0][1] == 'c')
			data->exit = ft_echo(data, cmd, fd_out);
		else if (cmd->value[0][1] == 'n')
			data->exit = ft_env(data, cmd, fd_out);
		else if (cmd->value[0][2] == 'i')
			data->exit = ft_exit(data, cmd, fd_out);
		else
			data->exit = ft_export(data, cmd, fd_out);
	}
	else if (cmd->value[0][0] == 'c')
		data->exit = ft_cd(data, cmd, fd_out);
	else if (cmd->value[0][0] == 'p')
		data->exit = ft_pwd(data, cmd, fd_out);
	else
		data->exit = ft_unset(data, cmd, fd_out);
}

void	built_in_parent_process(t_data *data, t_cmd *cmd)
{
	int	fd_out;

	if (cmd->fd[OUT])
		fd_out = cmd->fd[OUT];
	else
		fd_out = STDOUT_FILENO;
	built_in_cmd(data, cmd, fd_out);
	close_fds(cmd->fd[IN], cmd->fd[OUT], -1, -1);
}
