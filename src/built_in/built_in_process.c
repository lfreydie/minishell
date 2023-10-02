/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:55:09 by lfreydie          #+#    #+#             */
/*   Updated: 2023/10/02 13:00:55 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	built_in_process(t_data *data, t_token *token)
{
	pid_t	pid;

	if (pipe(data->pipefd) < 0)
		perror("pipe");
	pid = fork();
	if (pid < 0)
		return (perror("FORK"), 0);
	if (pid == 0)
	{
		redir(data, token);
		close_fds(data->tmp_fdin, data->pipefd[0], data->pipefd[1], -1);
		find_built_in(token);
		if (ft_strchr(token->cmd[0], '/'))
			execute_path(data, i); // not revised yet
		else
			execute(data, i); // not revised yet
		ft_exit(data, data->tab_cmd[i].cmd[0]); // not revised yet
	}
	close(data->tmp_fdin);
	close(data->pipefd[1]);
	data->tmp_fdin = data->pipefd[0];
	return (pid);
}

