/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:19:59 by lfreydie          #+#    #+#             */
/*   Updated: 2023/12/12 17:04:59 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_data *data, t_cmd __attribute__((unused)) *cmd, int fd_out)
{
	char	*path;

	path = gc(getcwd(NULL, 0));
	if (path)
	{
		ft_putendl_fd(path, fd_out);
		data->exit = 0;
	}
	else
		return (perror("getcwd"), FAILED);
	return (SUCCESS);
}
