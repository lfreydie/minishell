/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_modif.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:18:25 by lfreydie          #+#    #+#             */
/*   Updated: 2023/12/11 19:00:09 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_var(char ***env, char *var)
{
	char	**new_env;
	int		i;

	i = 0;
	if (ft_var_line((*env), var) >= 0)
		return (ft_replace_var(env, var));
	new_env = gc(malloc(sizeof(char **) * (ft_table_size(*env) + 2)));
	if (!new_env)
		return (ft_error_msg(SHELL, "add var", var, MALERR));
	while ((*env)[i])
	{
		new_env[i] = (*env)[i];
		i++;
	}
	new_env[i] = gc(ft_strdup(var));
	if (!new_env[i])
		return (ft_error_msg(SHELL, "add var", var, MALERR));
	ft_clean_var(&new_env[i]);
	new_env[i + 1] = NULL;
	(*env) = new_env;
}

void	ft_del_var(char ***env, int line)
{
	char	**new_env;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (line == -1)
		return ;
	new_env = gc(malloc(sizeof(char **) * (ft_table_size(*env))));
	if (!new_env)
		return (ft_error_msg(SHELL, "delete var", (*env)[line], MALERR));
	while ((*env)[i])
	{
		if (i == line)
			(*env)[i++] = NULL;
		else
			new_env[j++] = (*env)[i++];
	}
	new_env[j] = NULL;
	(*env) = new_env;
}

void	ft_replace_var(char ***env, char *var)
{
	int		line;
	char	*new_var;

	if (ft_var_line((*env), var) == -1)
		return (ft_add_var(env, var));
	line = ft_var_line((*env), var);
	new_var = gc(ft_strdup(var));
	if (!new_var)
		return (ft_error_msg(SHELL, "replace var", var, MALERR));
	(*env)[line] = new_var;
}

void	ft_append_var(char ***env, char *var)
{
	int		line;
	char	*new_var;
	char	*var_cpy;

	var_cpy = var;
	line = ft_var_line((*env), var);
	if (line == -1)
		return (ft_add_var(env, var));
	while (*var)
	{
		if (*var == '+' && *(var + 1) == '=')
			break ;
		var++;
	}
	var += 2;
	if (*var == '\0')
		return ;
	new_var = gc(ft_strjoin((*env)[line], var));
	if (!new_var)
		return (ft_error_msg(SHELL, "append var", var_cpy, MALERR));
	ft_replace_var(env, new_var);
}
