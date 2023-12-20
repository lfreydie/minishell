/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:17:10 by lfreydie          #+#    #+#             */
/*   Updated: 2023/12/20 21:51:29 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_update_oldpwd(t_data *data)
{
	int		line;
	char	*tmp;
	int		i;

	i = 0;
	line = ft_var_line(data->env, "PWD");
	if (line == -1)
		return (FAILED);
	while (data->env[line][i] != '=')
		i++;
	tmp = gc(ft_strjoin("OLDPWD=", data->env[line] + i + 1));
	ft_replace_var(&data->env, tmp);
	return (SUCCESS);
}

static int	ft_update_pwd(t_data *data)
{
	char	*tmp;
	char	*path;

	path = gc(getcwd(NULL, 0));
	tmp = gc(ft_strjoin("PWD=", path));
	ft_replace_var(&data->env, tmp);
	return (SUCCESS);
}

static char	*ft_home_old(t_data *data, t_cmd *cmd)
{
	char	*dir;

	if (!cmd->value[1] || cmd->value[1][0] == '~')
	{
		dir = ft_var_value(data->env, "HOME");
		if (!dir)
			return (ft_error_msg(SHELL, CD, cmd->value[1], HOMENS), NULL);
	}
	else
	{
		if (cmd->value[1][1] != '\0')
			return (ft_error_msg(SHELL, CD, cmd->value[1], INVOPT), NULL);
		dir = ft_var_value(data->env, "OLDPWD");
		if (!dir)
			return (ft_error_msg(SHELL, CD, cmd->value[1], OPWDNS), NULL);
	}
	return (dir);
}

int	ft_cd(t_data *data, t_cmd *cmd, int fd_out)
{
	char	*dir;

	if (cmd->n_args_cmd > 2)
		return (ft_error_msg(SHELL, CD, NULL, ARGNB), 1);
	if (!cmd->value[1] || (cmd->value[1][0] == '-' && cmd->value[1][1] == '\0') \
	|| (cmd->value[1][0] == '~' && cmd->value[1][1] == '\0'))
	{
		dir = ft_home_old(data, cmd);
		if (!dir)
			return (FAILED);
		if (chdir(dir) == -1)
			return (ft_error_msg(SHELL, CD, cmd->value[1], NULL), 127);
		if ((cmd->value[1] && cmd->value[1][0] == '-') \
		&& ft_pwd(data, NULL, fd_out) == FAILED)
			return (FAILED);
	}
	else if (chdir(cmd->value[1]) == -1)
		return (ft_error_msg(SHELL, CD, cmd->value[1], NOFLDIR), 1);
	if (ft_update_oldpwd(data))
		return (ft_error_msg(SHELL, CD, NULL, ERROLDPWD), 3);
	if (ft_update_pwd(data))
		return (ft_error_msg(SHELL, CD, NULL, ERRPWD), 3);
	__environ = data->env;
	return (SUCCESS);
}
