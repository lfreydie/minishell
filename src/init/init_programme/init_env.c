/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:01:19 by lefreydier        #+#    #+#             */
/*   Updated: 2023/12/11 21:56:12 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_env(t_data *data)
{
	char	*path;

	data->env = gc(ft_split(DEFAULT_ENV, ENV_SEP));
	path = gc(ft_strdup(DEFAULT_PATH));
	rm_node(data->env[0]);
	data->env[0] = path;
}

void	copy_env(t_data *data)
{
	int	i;
	int	env_size;

	i = 0;
	env_size = 0;
	while (__environ && __environ[env_size])
		env_size++;
	data->env = gc(ft_calloc(sizeof(char *), (env_size + 1)));
	while (i < env_size)
	{
		data->env[i] = gc(ft_strdup(__environ[i]));
		i++;
	}
}

void	init_env(t_data *data)
{
	if (!__environ || !*__environ)
		new_env(data);
	else
		copy_env(data);
	__environ = data->env;
}
