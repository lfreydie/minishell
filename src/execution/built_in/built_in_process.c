/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefreydier <lefreydier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:55:09 by lfreydie          #+#    #+#             */
/*   Updated: 2023/10/05 18:43:36 by lefreydier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_built_in_cmd(t_exec *exec)
{
	char	*cmd;

	cmd = exec->token->cmd[0];
	if (ft_strncmp(cmd, "pwd", ft_strlen(cmd)))
		ft_pwd();
	else if (ft_strncmp(cmd, "echo", ft_strlen(cmd)))
		ft_echo(exec->token->cmd);
	else if (ft_strncmp(cmd, "cd", ft_strlen(cmd)))
		ft_cd(exec->token->cmd);
	else if (ft_strncmp(cmd, "export", ft_strlen(cmd)))
		ft_export(exec->token->cmd);
	else if (ft_strncmp(cmd, "unset", ft_strlen(cmd)))
		ft_unset(exec->token->cmd);
	else if (ft_strncmp(cmd, "env", ft_strlen(cmd)))
		ft_env(exec->token->cmd);
	else if (ft_strncmp(cmd, "exit", ft_strlen(cmd)))
		ft_exit();
}

pid_t	built_in_child_process(t_exec *exec)
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
		find_built_in_cmd(exec);
		// free all for this process
		exit(1); // code erreur
	}
	close(exec->tmp_fdin);
	close(exec->pipefd[1]);
	exec->tmp_fdin = exec->pipefd[0];
	return (pid);
}

void	built_in_parent_process(t_exec *exec)
{
	t_tok	*token;
	int		fd;

	token = exec->token;
	if (token->redir_in)
	{
		fd = open(token->redir_in, O_RDONLY);
		if (fd < 0)
			perror(ERR_NOP);
		if (dup2(fd, STDIN_FILENO) < 0)
			perror("dup2");
		close(fd);
	}
	if (token->redir_out)
	{
		if (token->append)
			fd = open(token->redir_out, O_RDWR | O_CREAT | O_APPEND, 0644);
		else
			fd = open(token->redir_out, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			perror(ERR_NOP);
		if (dup2(fd, STDIN_FILENO) < 0)
			perror("dup2");
		close(fd);
	}
}