/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:13:16 by lfreydie          #+#    #+#             */
/*   Updated: 2023/12/19 00:06:19 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	launch_exec_process(t_data *data)
{
	if (data->num_cmd == 1 && data->lst_cmd->built_in)
		built_in_parent_process(data, data->lst_cmd);
	else
		pipex_process(data);
}

void	pipex_process(t_data *data)
{
	t_cmd	*cmd;
	pid_t	pid;
	int		status;
	int		i;

	cmd = data->lst_cmd;
	while (cmd)
	{
		cmd->pid = fork_process(data, cmd);
		pid = cmd->pid;
		cmd = cmd->next;
	}
	close(data->tmp_fdin);
	i = -1;
	waitpid(pid, &status, 0);
	while (++i < data->num_cmd - 1)
		wait(0);
}

pid_t	fork_process(t_data *data, t_cmd *cmd)
{
	pid_t	pid;

	if (pipe(data->pipefd) < 0)
		perror("pipe");
	pid = fork();
	if (pid == 0)
	{
		exec_redir_in(data, cmd);
		exec_redir_out(data, cmd);
		close_fds(data->tmp_fdin, data->pipefd[0], data->pipefd[1], -1);
		if (cmd->launch == FALSE)
			exit(data->exit);
		else if (cmd->built_in)
			built_in_cmd(data, cmd, cmd->fd[OUT]);
		else if (ft_strchr(cmd->value[0], '/'))
			execute_path(data, cmd);
		else
			execute(data, cmd);
		exit(data->exit);
	}
	close_fds(data->tmp_fdin, data->pipefd[1], cmd->fd[IN], cmd->fd[OUT]);
	data->tmp_fdin = data->pipefd[0];
	return (pid);
}

void	exec_redir_in(t_data *data, t_cmd *cmd)
{
	if (cmd->fd[IN] > 0)
	{
		if (cmd->id != 1)
			close(data->tmp_fdin);
		data->tmp_fdin = cmd->fd[IN];
	}
	if (data->tmp_fdin > 0 && dup2(data->tmp_fdin, STDIN) < 0)
		perror("dup2");
}

void	exec_redir_out(t_data *data, t_cmd *cmd)
{
	if (cmd->fd[OUT] > 0)
	{
		if (dup2(cmd->fd[OUT], STDOUT) < 0)
			perror("dup2");
		close(cmd->fd[OUT]);
	}
	else if (cmd->next)
	{
		if (dup2(data->pipefd[1], STDOUT) < 0)
			perror("dup2");
		cmd->fd[OUT] = data->pipefd[1];
	}
}
