/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:19:07 by lfreydie          #+#    #+#             */
/*   Updated: 2023/12/20 22:09:51 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_newline(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-' || str[i + 1] != 'n')
		return (0);
	i += 2;
	while (str[i])
	{
		if (str[i] == 'n')
			i++;
		if (str[i] == '\0' || (str[i] == ' ' && str[i + 1] == '\0'))
			break ;
		if (str[i] != 'n')
			return (0);
	}
	return (1);
}

void	ft_echo_while(char **argv, int i, bool *newline, int fd_out)
{
	int		flag;

	flag = 0;
	while (argv[i])
	{
		if (*newline && !flag && ft_newline(argv[i]))
		{
			i++;
			continue ;
		}
		else
			flag = 1;
		ft_putstr_fd(argv[i], fd_out);
		if (argv[i + 1])
			ft_putstr_fd(" ", fd_out);
		i++;
	}
}

int	ft_echo(t_data __attribute((unused)) *data, t_cmd *cmd, int fd_out)
{
	bool	newline;
	int		i;

	newline = 0;
	i = 1;
	if (!cmd->value[1])
		return (ft_putchar_fd('\n', fd_out), SUCCESS);
	newline = ft_newline(cmd->value[1]);
	if (newline)
		i++;
	ft_echo_while(cmd->value, i, &newline, fd_out);
	if (!newline)
		ft_putchar_fd('\n', fd_out);
	return (SUCCESS);
}
