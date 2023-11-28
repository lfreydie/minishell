/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefreydier <lefreydier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:13:16 by lfreydie          #+#    #+#             */
/*   Updated: 2023/11/28 10:28:24 by lefreydier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	launch_exec_process(t_data *data)
{
	t_exec	*exec;

	exec = ft_calloc(sizeof(t_exec), 1);
	if (!exec)
		perror("ERR_MAL");
	exec->data = data;
	exec->l_cmd = data->lst_cmd;
	if (data->num_cmd == 1 && exec->l_cmd->built_in)
		built_in_parent_process(exec);
	else
		pipex_process(exec);
}

void	pipex_process(t_exec *exec)
{
	int		status;
	int		i;
	int		pid;

	while (exec->l_cmd)
	{
		if (exec->l_cmd->built_in)
			exec->l_cmd->pid = built_in_child_process(exec);
		else
			exec->l_cmd->pid = fork_process(exec);
		if (exec->l_cmd->io_red->op == HEREDOC_RED)
			unlink(exec->l_cmd->io_red->redir);
		pid = exec->l_cmd->pid;
		exec->l_cmd = exec->l_cmd->next;
	}
	close(exec->tmp_fdin);
	i = -1;
	waitpid(pid, &status, 0);
	while (++i < exec->data->num_cmd - 1)
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
		if (ft_strchr(exec->l_cmd->cmd_value[0], '/'))
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
	t_cmd	*cmd;

	cmd = exec->l_cmd;
	if (cmd->io_red->op == HEREDOC_RED || cmd->io_red->op == IN_RED)
	{
		if (cmd->id != 1)
			close(exec->tmp_fdin);
		exec->tmp_fdin = open(cmd->io_red->redir, O_RDONLY);
	}
	if (cmd->id != 1 || cmd->io_red->op == HEREDOC_RED || cmd->io_red->op == IN_RED)
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
	t_cmd	*cmd;

	cmd = exec->l_cmd;
	if (cmd->io_red->op == OUTAP_RED || cmd->io_red->op == OUTTR_RED)
	{
		if (cmd->io_red-> op == OUTAP_RED)
			fd_out = open(cmd->io_red->redir, \
			O_RDWR | O_CREAT | O_APPEND, 0644);
		else
			fd_out = open(cmd->io_red->redir, \
			O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd_out >= 0 && dup2(fd_out, STDOUT_FILENO) < 0)
			perror("dup2");
		else if (fd_out < 0)
			(close_fds(exec->tmp_fdin, exec->pipefd[0], exec->pipefd[1], -1));
		close(fd_out);
	}
	else if (cmd->next)
	{
		if (dup2(exec->pipefd[1], STDOUT_FILENO) < 0)
			perror("dup2");
	}
}
