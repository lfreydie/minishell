/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:26:46 by lfreydie          #+#    #+#             */
/*   Updated: 2023/12/11 18:51:47 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	**get_paths(t_exec *exec)
{
	char		*env_path;
	char		**paths;
	int			i;

	i = 0;
	if (!exec->data->env)
		return (NULL);
	while (exec->data->env[i])
	{
		env_path = ft_strnstr(exec->data->env[i], "PATH=", 5);
		if (env_path)
			break ;
		i++;
	}
	if (!env_path)
		exit(1); // code erreur
	paths = ft_split(env_path + 5, ':');
	if (!paths)
		exit(1); // code erreur
	return (paths);
}

void	execute(t_exec *exec)
{
	char		**paths;
	char		*path_cmd;
	int			i;

	i = 0;
	printf("e.0\n");
	paths = get_paths(exec);
	printf("e.1\n");
	while (paths[i])
	{
		path_cmd = get_path_cmd(paths[i], exec->l_cmd->value[0]);
		printf("e.2\n");
		if (!access(path_cmd, F_OK))
		{
			printf("e.3\n");
			execve(path_cmd, exec->l_cmd->value, exec->data->env);
			perror(path_cmd);
		}
		free(path_cmd);
		i++;
		printf("e.4\n");
	}
	free_tab(paths);
	printf("e.5\n");
	return ;
}

void	execute_path(t_exec *exec)
{
	if (!access(exec->l_cmd->value[0], X_OK))
		execve(exec->l_cmd->value[0], exec->l_cmd->value, exec->data->env);
	if (access(exec->l_cmd->value[0], F_OK))
		execute(exec);
	return ;
}
