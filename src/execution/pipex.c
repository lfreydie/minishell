/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefreydier <lefreydier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:13:16 by lfreydie          #+#    #+#             */
/*   Updated: 2023/10/06 17:59:10 by lefreydier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	launch_exec_process(t_data *data)
{
	t_exec	*exec;

	exec = ft_calloc(sizeof(t_exec *), 1);
	if (!exec)
		perror(ERR_MAL);
	exec->data = data;
	exec->token = data->head;
	if (data->num_tokens == 1 && exec->token->built_in)
		built_in_parent_process(exec);
	else
		pipex_process(exec);
}

void	pipex_process(t_exec *exec)
{
	int		status;
	int		i;

	while (exec->token)
	{
		if (exec->token->built_in)
			exec->token->pid = built_in_child_process(exec);
		else
			exec->token->pid = fork_process(exec);
		if (exec->token->heredoc)
			unlink(exec->token->redir_in);
		exec->token = exec->token->next;
	}
	close(exec->tmp_fdin);
	i = -1;
	waitpid(exec->token->pid, &status, 0);
	while (++i < exec->data->num_tokens - 1)
		wait(0);
}

pid_t	fork_process(t_exec *exec)
{
	pid_t	pid;

	if (pipe(exec->pipefd) < 0)
		perror("pipe");
	pid = fork();
	if (pid < 0)
		return (perror("FORK"), 0);
	if (pid == 0)
	{
		exec_redir_in(exec);
		exec_redir_out(exec);
		close_fds(exec->tmp_fdin, exec->pipefd[0], exec->pipefd[1], -1);
		if (ft_strchr(exec->token->cmd[0], '/'))
			execute_path(exec);
		else
			execute(exec);
		exit(1); // code erreur
	}
	close(exec->tmp_fdin);
	close(exec->pipefd[1]);
	exec->tmp_fdin = exec->pipefd[0];
	return (pid);
}

void	exec_redir_in(t_exec *exec)
{
	t_tok	*token;

	token = exec->token;
	if (token->redir_in)
	{
		if (token->id != 1)
			close(exec->tmp_fdin);
		exec->tmp_fdin = open(token->redir_in, O_RDONLY);
	}
	if (token->id != 1 || token->redir_in)
	{
		if (exec->tmp_fdin >= 0 && dup2(exec->tmp_fdin, STDIN_FILENO) < 0)
			perror("dup2");
		else if (exec->tmp_fdin < 0)
			(close_fds(exec->pipefd[0], exec->pipefd[1], -1, -1));
	}
}

void	exec_redir_out(t_exec *exec)
{
	int		fd_out;
	t_tok	*token;

	token = exec->token;
	if (token->redir_out)
	{
		if (token->append)
			fd_out = open(token->redir_out, O_RDWR | O_CREAT | O_APPEND, 0644);
		else
			fd_out = open(token->redir_out, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd_out >= 0 && dup2(fd_out, STDOUT_FILENO) < 0)
			perror("dup2");
		else if (fd_out < 0)
			(close_fds(exec->tmp_fdin, exec->pipefd[0], exec->pipefd[1], -1));
		close(fd_out);
	}
	else if (!token->next)
	{
		if (dup2(exec->pipefd[1], STDOUT_FILENO) < 0)
			perror("dup2");
	}
}
