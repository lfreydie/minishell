/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:21:39 by lfreydie          #+#    #+#             */
/*   Updated: 2023/12/15 18:02:06 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_data *data, t_cmd *cmd, int __attribute((unused)) fd_out)
{
	int	var_l;
	int	i;

	i = 1;
	if (!cmd->value[1])
		return (0);
	while (cmd->value[i])
	{
		if (cmd->value[i][0] == '-')
			i++;
		else if (ft_check_arg(cmd->value[i]) == FAILED)
			i++;
		else
		{
			var_l = ft_var_line(data->env, cmd->value[i++]);
			if (var_l >= 0)
				ft_del_var(&data->env, var_l);
		}
	}
	__environ = data->env;
	return (SUCCESS);
}
