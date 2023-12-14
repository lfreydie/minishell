/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:22:43 by lfreydie          #+#    #+#             */
/*   Updated: 2023/12/12 16:50:20 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_data *data, t_cmd *cmd, int fd_out)
{
	int	exit_status;

	(void)fd_out;
	if (cmd->n_args_cmd > 2)
		return (ft_error_msg(SHELL, EXT, NULL, ARGNB), 2);
	if (cmd->value[1])
		exit_status = (ft_atoi(cmd->value[1]) % 256);
	else
		exit_status = 0;
	data->exit = exit_status;
	ft_putstr_fd("exit\n", 1);
	gc_collect();
	return (exit_status);
}
