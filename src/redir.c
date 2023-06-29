/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:54:20 by lfreydie          #+#    #+#             */
/*   Updated: 2023/06/29 14:56:57 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/pipex.h"

void	redir(t_pipex *infos, int i)
{
	int	io_fd;

	if (infos->tmp_fdin >= 0 && dup2(infos->tmp_fdin, STDIN_FILENO) < 0)
		perror("dup2");
	else if (infos->tmp_fdin < 0)
		(close_fds(infos->pipefd[0], infos->pipefd[1], \
		-1, -1), ft_exit(infos, NULL));
	if (i == infos->ncmd - 1)
	{
		if (!infos->heredoc)
			io_fd = open(infos->outfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
		else
			io_fd = open(infos->outfile, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (io_fd < 0)
			(close_fds(infos->tmp_fdin, infos->pipefd[0], \
			infos->pipefd[1], -1), ft_exit(infos, infos->outfile));
		if (io_fd >= 0 && dup2(io_fd, STDOUT_FILENO) < 0)
			perror("dup2");
		close(io_fd);
	}
	else
	{
		if (dup2(infos->pipefd[1], STDOUT_FILENO) < 0)
			perror("dup2");
	}
}
