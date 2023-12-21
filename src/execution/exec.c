/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:26:46 by lfreydie          #+#    #+#             */
/*   Updated: 2023/12/21 01:18:19 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path_cmd(char *paths, char *cmd)
{
	char	*tmp;
	char	*path;

	tmp = gc(ft_strjoin(paths, "/"));
	path = gc(ft_strjoin(tmp, cmd));
	free_node(tmp);
	return (path);
}

char	**get_paths(t_data *data)
{
	char		*env_path;
	char		**paths;

	if (!data->env)
		return (NULL);
	env_path = getenv("PATH");
	if (env_path)
		paths = gc(ft_split(env_path + 5, ':'));
	else
		return (NULL);
	return (paths);
}

void	error_set_up(t_data *data, t_cmd *cmd)
{
	ft_error_msg(SHELL, cmd->value[0], NULL, PERDEN);
	data->exit = 126;
}

void	execute(t_data *data, t_cmd *cmd)
{
	char		**paths;
	char		*path_cmd;
	struct stat	stats;
	int			i;

	i = -1;
	paths = get_paths(data);
	if (!paths)
		execute_path(data, cmd);
	while (paths[++i])
	{
		path_cmd = get_path_cmd(paths[i], cmd->value[0]);
		stat(path_cmd, &stats);
		if (!access(path_cmd, F_OK) && !S_ISDIR(stats.st_mode))
		{
			if (!access(path_cmd, X_OK))
				execve(path_cmd, cmd->value, data->env);
			else
			{
				error_set_up(data, cmd);
				return ;
			}
		}
	}
	(ft_error_msg(SHELL, cmd->value[0], NULL, CMDERR), data->exit = 127);
}

void	execute_path(t_data *data, t_cmd *cmd)
{
	struct stat	stats;

	if (access(cmd->value[0], F_OK))
	{
		ft_error_msg(SHELL, cmd->value[0], NULL, NOFLDIR);
		data->exit = 127;
		return ;
	}
	stat(cmd->value[0], &stats);
	if (S_ISDIR(stats.st_mode))
	{
		ft_error_msg(SHELL, cmd->value[0], NULL, ISDIRE);
		data->exit = 126;
		return ;
	}
	if (!access(cmd->value[0], X_OK))
		execve(cmd->value[0], cmd->value, data->env);
	else
	{
		ft_error_msg(SHELL, cmd->value[0], NULL, PERDEN);
		data->exit = 126;
	}
	return ;
}
