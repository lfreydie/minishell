/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:20:59 by lfreydie          #+#    #+#             */
/*   Updated: 2023/12/20 21:25:54 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_dup_env(char **env)
{
	char	**export;
	int		size;
	int		i;

	i = 0;
	size = ft_table_size(env);
	export = gc(malloc(sizeof(char **) * (size + 1)));
	if (!export)
		return (ft_error_msg(SHELL, EXP, NULL, MALERR), NULL);
	while (env[i])
	{
		export[i] = gc(ft_strdup(env[i]));
		if (!export[i])
			return (ft_error_msg(SHELL, EXP, env[i], MALERR), NULL);
		i++;
	}
	export[i] = NULL;
	return (export);
}

static void	ft_sort_export(char ***export)
{
	char	*tmp;
	int		i;
	int		j;
	int		size;

	size = ft_table_size(*export);
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size - 1 - i)
		{
			if (ft_strccmp((*export)[j], (*export)[j + 1], '=') > 0)
			{
				tmp = (*export)[j];
				(*export)[j] = (*export)[j + 1];
				(*export)[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static int	ft_print_export(t_data *data, int fd_out)
{
	char	**export;
	int		i;

	export = ft_dup_env(data->env);
	if (!export)
		return (FAILED);
	ft_sort_export(&export);
	i = 0;
	while (export[i])
	{
		ft_putstr_fd("export ", fd_out);
		ft_putendl_fd(export[i++], fd_out);
	}
	return (SUCCESS);
}

int	ft_export_while(t_data *data, char **argv, int i)
{
	while (argv[i])
	{
		if (argv[i][0] == '-')
			return (ft_error_msg(SHELL, EXP, argv[i], IVALOP), 2);
		if (ft_check_arg(argv[i]) == FAILED)
		{
			data->exit = 1;
			ft_error_msg(SHELL, EXP, argv[i++], IVALID);
		}
		else if (ft_var_line(data->env, argv[i]) >= 0)
		{
			if (ft_sign_append(argv[i]) == TRUE)
				ft_append_var(&data->env, argv[i++]);
			else
				ft_replace_var(&data->env, argv[i++]);
		}
		else if (ft_var_line(data->env, argv[i]) >= 0
			&& ft_value_is_empty(argv[i]) == TRUE)
			i++;
		else
			ft_add_var(&data->env, argv[i++]);
	}
	return (data->exit);
}

int	ft_export(t_data *data, t_cmd *cmd, int fd_out)
{
	data->exit = 0;
	if (cmd->n_args_cmd == 1)
		return (ft_print_export(data, fd_out));
	data->exit = ft_export_while(data, cmd->value, 1);
	__environ = data->env;
	return (data->exit);
}
