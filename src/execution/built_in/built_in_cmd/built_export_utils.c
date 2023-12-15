/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:10:22 by lfreydie          #+#    #+#             */
/*   Updated: 2023/12/15 18:10:10 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_arg(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] && (ft_isalpha(arg[0]) == 1 || arg[0] == '_'))
		i++;
	else
		return (FAILED);
	while (arg[i])
	{
		if (arg[i] == '=')
			return (SUCCESS);
		else if (arg[i] == '+' && arg[i + 1] == '=')
			return (SUCCESS);
		if (ft_isalnum(arg[i]) == 0)
		{
			if (arg[i] == '_')
				i++;
			else
				return (FAILED);
		}
		i++;
	}
	return (SUCCESS);
}

int	ft_sign_append(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '+' && arg[i + 1] == '=')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	ft_value_is_empty(char *arg)
{
	int		flag;
	int		i;

	i = 0;
	flag = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			flag++;
		i++;
	}
	if ((arg[i--] == '=' && flag == 1) || flag == 0)
		return (TRUE);
	return (FALSE);
}

int	ft_var_line(char **tab, char *var)
{
	int	i;
	int	j;

	i = 0;
	if (!var)
		return (-1);
	while (tab[i])
	{
		j = 0;
		while (tab[i][j] == var[j] && var[j] && tab[i][j])
		{
			if (tab[i][j + 1] == '='
			&& (var[j + 1] == '=' || var[j + 1] == '\0'
			|| (var[j + 1] == '+' && var[j + 2] == '=')))
				return (i);
			if (tab[i][j + 1] == '\0'
			&& (var[j + 1] == '=' || var[j + 1] == '\0'
			|| (var[j + 1] == '+' && var[j + 2] == '=')))
				return (i);
			j++;
		}
		i++;
	}
	return (FAILED);
}
