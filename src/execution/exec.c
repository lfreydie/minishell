/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:26:46 by lfreydie          #+#    #+#             */
/*   Updated: 2023/12/19 00:16:56 by lfreydie         ###   ########.fr       */
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
	paths = gc(ft_split(env_path + 5, ':'));
	free_node(env_path);
	return (paths);
}

void	execute(t_data *data, t_cmd *cmd)
{
	char		**paths;
	char		*path_cmd;
	int			i;

	i = 0;
	paths = get_paths(data);
	while (paths[i])
	{
		path_cmd = get_path_cmd(paths[i], cmd->value[0]);
		if (!access(path_cmd, F_OK))
		{
			execve(path_cmd, cmd->value, data->env);
			perror(path_cmd);
		}
		i++;
	}
	ft_error_msg(NULL, cmd->value[0], NULL, CMDERR);
	data->exit = 127;
	return ;
}

void	execute_path(t_data *data, t_cmd *cmd)
{
	if (!access(cmd->value[0], X_OK))
		execve(cmd->value[0], cmd->value, data->env);
	if (access(cmd->value[0], F_OK))
		execute(data, cmd);
	return ;
}
