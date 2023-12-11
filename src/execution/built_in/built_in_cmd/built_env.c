/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:22:19 by lfreydie          #+#    #+#             */
/*   Updated: 2023/12/11 18:57:32 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_data *data, t_cmd *cmd, int fd_out)
{
	int	i;
	int	j;

	i = 0;
	if (cmd->n_args_cmd > 1)
		return (FAILED);
	if (!data || !data->env)
		return (printf("ERR ENV"), 1);
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
	return (0);
}
