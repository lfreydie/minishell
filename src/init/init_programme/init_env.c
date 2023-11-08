/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefreydier <lefreydier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:01:19 by lefreydier        #+#    #+#             */
/*   Updated: 2023/10/26 14:51:49 by lefreydier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_env(t_data *data)
{
	char	*path;

	data->env = ft_split(DEFAULT_ENV, ENV_SEP);
	if (!data->env)
		exit(1); // code erreur 139
	path = ft_strdup(DEFAULT_PATH);
	if (!path)
		exit(1); // code erreur 139
	free(data->env[0]);
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
	data->env = ft_calloc(sizeof(char *), (env_size + 1));
	if (!data->env)
		exit(1); // code erreur 139
	while (i < env_size)
	{
		data->env[i] = ft_strdup(__environ[i]);
		if (!data->env[i])
			exit(1); // code erreur 139
		i++;
	}
}

void	init_env(t_data *data)
{
	if (!__environ || !*__environ)
		new_env(data);
	else
		copy_env(data);
	if (!data->env)
		exit (1); // code erreur
	__environ = data->env;
}