/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:22:43 by lfreydie          #+#    #+#             */
/*   Updated: 2023/12/20 22:44:11 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_data *data, t_cmd *cmd, int fd_out)
{
	int	i;

	(void)fd_out;
	if (cmd->n_args_cmd > 2)
		return (ft_error_msg(SHELL, EXT, NULL, ARGNB), 1);
	if (cmd->value[1])
	{
		i = 0;
		if (cmd->value[1][i] == '-' || cmd->value[1][i] == '+')
			i++;
		while (cmd->value[1][i])
		{
			if (!ft_isdigit(cmd->value[1][i]))
				return (ft_error_msg(SHELL, EXT, NULL, NUMREQ), 2);
			i++;
		}
		data->exit = (ft_atoi(cmd->value[1]) % 256);
	}
	ft_putstr_fd("exit\n", 1);
	gc_collect();
	exit(data->exit);
}
