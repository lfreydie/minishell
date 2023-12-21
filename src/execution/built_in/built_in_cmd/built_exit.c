/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:22:43 by lfreydie          #+#    #+#             */
/*   Updated: 2023/12/21 01:18:54 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_str_is_digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_data *data, t_cmd *cmd, int fd_out)
{
	(void)fd_out;
	if (cmd->n_args_cmd > 2)
	{
		if (!ft_str_is_digit(cmd->value[1]))
		{
			ft_error_msg(SHELL, EXT, NULL, NUMREQ);
			data->exit = 2;
			gc_collect();
			exit(data->exit);
		}
		return (ft_error_msg(SHELL, EXT, NULL, ARGNB), 1);
	}
	if (cmd->value[1])
	{
		if (!ft_str_is_digit(cmd->value[1]))
			return (ft_error_msg(SHELL, EXT, NULL, NUMREQ), 2);
		data->exit = (ft_atoi(cmd->value[1]) % 256);
	}
	ft_putstr_fd("exit\n", 1);
	gc_collect();
	exit(data->exit);
}
