/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 19:32:22 by lfreydie          #+#    #+#             */
/*   Updated: 2023/12/20 22:33:27 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_err_syntax(t_data *data, char *shell, char *msg, char *str)
{
	if (shell)
	{
		ft_putstr_fd(shell, 2);
		ft_putstr_fd(": ", 2);
	}
	if (msg)
	{
		ft_putstr_fd(" ", 2);
		ft_putstr_fd(msg, 2);
	}
	if (str)
	{
		ft_putstr_fd(": '", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("'", 2);
	}
	ft_putstr_fd("\n", 2);
	data->exit = 2;
}

void	ft_error_msg(char *shell, char *cmd, char *arg, char *error)
{
	if (shell)
	{
		ft_putstr_fd(shell, 2);
		ft_putstr_fd(": ", 2);
	}
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	if (error)
	{
		ft_putstr_fd(error, 2);
		ft_putstr_fd("\n", 2);
	}
	else
		perror(NULL);
}

void	msg_err_sys(char *msg)
{
	if (msg)
	{
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("\n", 2);
	}
}

void	err_sys(char *msg)
{
	msg_err_sys(msg);
	gc_collect();
	exit (1);
}
