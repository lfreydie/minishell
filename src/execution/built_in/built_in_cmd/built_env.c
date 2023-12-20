/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:22:19 by lfreydie          #+#    #+#             */
/*   Updated: 2023/12/19 18:54:01 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_data *data, t_cmd *cmd, int fd_out)
{
	int	i;
	int	j;

	i = 0;
	if (cmd->n_args_cmd > 1)
		return (ft_error_msg(SHELL, ENV, NULL, ARGNB), data->exit = 2, FAILED);
	if (!data->env)
		init_env(data);
	while (data->env[i])
	{
		j = 0;
		while (data->env[i][j] && data->env[i][j] != '=')
			j++;
		if (data->env[i][j] == '\0')
			i++;
		else
		{
			ft_putendl_fd(data->env[i], fd_out);
			i++;
		}
	}
	return (data->exit = 0, 0);
}
