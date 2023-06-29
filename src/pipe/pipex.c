/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:13:16 by lfreydie          #+#    #+#             */
/*   Updated: 2023/06/29 14:26:16 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_pipex	*infos;

	if (ac < 5)
		return (ft_exit(NULL, ERR_ARG), 127);
	infos = init_struct(ac, av, envp);
	pipex_process(infos);
	if (infos->heredoc)
		unlink(infos->infile);
	free_infos(infos);
	return (0);
}

void	pipex_process(t_pipex *infos)
{
	int	status;
	int	i;

	infos->tmp_fdin = open(infos->infile, O_RDONLY);
	if (infos->tmp_fdin < 0)
		perror(infos->infile);
	i = -1;
	while (++i < infos->ncmd)
		infos->tab_cmd[i].pid = fork_process(infos, i);
	close(infos->tmp_fdin);
	i = -1;
	waitpid(infos->tab_cmd[infos->ncmd - 1].pid, &status, 0);
	while (++i < infos->ncmd - 1)
		wait(0);
}

pid_t	fork_process(t_pipex *infos, int i)
{
	pid_t	pid;

	if (pipe(infos->pipefd) < 0)
		perror("pipe");
	pid = fork();
	if (pid < 0)
		return (perror("FORK"), 0);
	if (pid == 0)
	{
		redir(infos, i);
		close_fds(infos->tmp_fdin, infos->pipefd[0], infos->pipefd[1], -1);
		if (ft_strchr(infos->tab_cmd[i].cmd[0], '/'))
			execute_path(infos, i);
		else
			execute(infos, i);
		ft_exit(infos, infos->tab_cmd[i].cmd[0]);
	}
	close(infos->tmp_fdin);
	close(infos->pipefd[1]);
	infos->tmp_fdin = infos->pipefd[0];
	return (pid);
}

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
