/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:13:16 by lfreydie          #+#    #+#             */
/*   Updated: 2023/10/02 12:56:06 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// int	main(int ac, char **av, char **envp)
// {
// 	t_pipex	*infos;

// 	if (ac < 5)
// 		return (ft_exit(NULL, ERR_ARG), 127);
// 	infos = init_struct(ac, av, envp);
// 	pipex_process(infos);
// 	if (infos->heredoc)
// 		unlink(infos->infile);
// 	free_infos(infos);
// 	return (0);
// }

void	pipex_process(t_data *data)
{
	int		status;
	int		i;
	t_tok	*token;

	token = data->head;
	while (token)
	{
		if (token->built_in)
			token->pid = built_in_process(data, token);
		else
			token->pid = fork_process(data, token);
		token = token->next;
	}
	close(data->tmp_fdin);
	i = -1;
	waitpid(token->pid, &status, 0);
	while (++i < data->num_tokens - 1)
		wait(0);
}

pid_t	fork_process(t_data *data, t_tok *token)
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

// void	redir(t_pipex *infos, int i)
// {
// 	int	io_fd;

// 	if (infos->tmp_fdin >= 0 && dup2(infos->tmp_fdin, STDIN_FILENO) < 0)
// 		perror("dup2");
// 	else if (infos->tmp_fdin < 0)
// 		(close_fds(infos->pipefd[0], infos->pipefd[1], \
// 		-1, -1), ft_exit(infos, NULL));
// 	if (i == infos->ncmd - 1)
// 	{
// 		if (!infos->heredoc)
// 			io_fd = open(infos->outfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
// 		else
// 			io_fd = open(infos->outfile, O_RDWR | O_CREAT | O_APPEND, 0644);
// 		if (io_fd < 0)
// 			(close_fds(infos->tmp_fdin, infos->pipefd[0], \
// 			infos->pipefd[1], -1), ft_exit(infos, infos->outfile));
// 		if (io_fd >= 0 && dup2(io_fd, STDOUT_FILENO) < 0)
// 			perror("dup2");
// 		close(io_fd);
// 	}
// 	else
// 	{
// 		if (dup2(infos->pipefd[1], STDOUT_FILENO) < 0)
// 			perror("dup2");
// 	}
// }

void	redir(t_data *data, t_tok *token)
{
	int	fd_out;

	if (token->redir_in)
	{
		if (token->id != 1)
			close(data->tmp_fdin);
		data->tmp_fdin = open(token->redir_in, O_RDONLY);
	}
	if (token->id != 1 || token->redir_in)
	{
		if (data->tmp_fdin >= 0 && dup2(data->tmp_fdin, STDIN_FILENO) < 0)
			perror("dup2");
		else if (data->tmp_fdin < 0)
			(close_fds(data->pipefd[0], data->pipefd[1], -1, -1)); // close fds if tmp_fdin doesn't open
	}
	if (token->redir_out)
	{
		if (token->append)
			fd_out = open(token->redir_out, O_RDWR | O_CREAT | O_APPEND, 0644);
		else
			fd_out = open(token->redir_out, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd_out >= 0 && dup2(fd_out, STDOUT_FILENO) < 0)
			perror("dup2");
		else if (fd_out < 0)
			(close_fds(data->tmp_fdin, data->pipefd[0], data->pipefd[1], -1)); // close fds if fd_out doesn't open
		close(fd_out);
	}
	else if (!token->next)
	{
		if (dup2(data->pipefd[1], STDOUT_FILENO) < 0)
			perror("dup2");
	}
}
