/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefreydier <lefreydier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:26:46 by lfreydie          #+#    #+#             */
/*   Updated: 2023/10/05 17:59:18 by lefreydier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path_cmd(char *paths, char *cmd)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(paths, "/");
	if (!tmp)
		perror("get_path_cmd");
	path = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!path)
		perror("get_path_cmd");
	return (path);
}

char	**get_paths(t_pipex *infos)
{
	char		*env_path;
	char		**paths;
	int			i;

	i = 0;
	if (!infos->env)
		return (NULL);
	while (infos->env[i])
	{
		env_path = ft_strnstr(infos->env[i], "PATH=", 5);
		if (env_path)
			break ;
		i++;
	}
	if (!env_path)
		ft_exit(infos, NULL);
	paths = ft_split(env_path + 5, ':');
	if (!paths)
		ft_exit(infos, ERR_MAL);
	return (paths);
}

void	execute(t_pipex *infos, int i)
{
	char		**paths;
	char		*path_cmd;
	int			n;

	n = 0;
	paths = get_paths(infos);
	while (paths[n])
	{
		path_cmd = get_path_cmd(paths[n], infos->tab_cmd[i].cmd[0]);
		if (!access(path_cmd, F_OK))
		{
			execve(path_cmd, infos->tab_cmd[i].cmd, infos->env);
			perror(path_cmd);
		}
		free(path_cmd);
		n++;
	}
	free_tab(paths);
	return ;
}

void	execute_path(t_pipex *infos, int i)
{
	if (!access(infos->tab_cmd[i].cmd[0], X_OK))
		execve(infos->tab_cmd[i].cmd[0], infos->tab_cmd[i].cmd, infos->env);
	if (access(infos->tab_cmd[i].cmd[0], F_OK))
		execute(infos, i);
	return ;
}
