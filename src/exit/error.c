/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 19:32:22 by lfreydie          #+#    #+#             */
/*   Updated: 2023/12/12 19:41:03 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_err_syntax(char *shell, char *msg, char *str)
{
	int	fd;

	fd = dup(STDOUT_FILENO);
	dup2(2, 1);
	if (shell)
		printf("%s: ", shell);
	if (msg)
		printf(" %s", msg);
	if (str)
		printf(": '%s'", str);
	printf("\n");
	dup2(1, fd);
	close(fd);
}

void	ft_error_msg(char *shell, char *cmd, char *arg, char *error)
{
	int	fd;

	fd = dup(STDOUT_FILENO);
	dup2(2, 1);
	if (shell)
		printf("%s: ", shell);
	if (cmd)
		printf("%s: ", cmd);
	if (arg)
		printf("%s: ", arg);
	if (error)
	{
		printf("%s", error);
		printf("\n");
	}
	else
		perror(NULL);
	dup2(1, fd);
	close(fd);
}

void	msg_err_sys(char *msg)
{
	int	fd;

	fd = dup(STDOUT_FILENO);
	dup2(2, 1);
	if (msg)
		printf("%s\n", msg);
	dup2(1, fd);
	close(fd);
}

void	err_sys(char *msg)
{
	msg_err_sys(msg);
	gc_collect();
	exit (1);
}
