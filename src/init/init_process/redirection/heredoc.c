/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:36:31 by lefreydier        #+#    #+#             */
/*   Updated: 2023/12/21 00:37:25 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_write(t_data *data, char *limiter, t_cmd *cmd)
{
	int		flag;
	char	*line;

	(void)data;
	flag = 1;
	while (flag)
	{
		line = gc_null(readline("> "));
		if (!line)
		{
			ft_error_msg(SHELL, "warning", NULL, \
			"here-document delimited by end-of-file (wanted `eof')");
			close(cmd->fd[IN]);
			return ;
		}
		if (!ft_streq(line, limiter))
		{
			write(cmd->fd[IN], line, ft_strlen(line));
			write(cmd->fd[IN], "\n", 1);
		}
		else
			flag = 0;
		free_node(line);
	}
	close(cmd->fd[IN]);
}

char	*heredoc_name(void)
{
	static int	counter = 0;
	char		*count_s;
	char		*name;

	while (1)
	{
		count_s = gc(ft_itoa(counter));
		name = gc(ft_strjoin("/tmp/heredoc_", count_s));
		free_node(count_s);
		if (access(name, F_OK))
			break ;
		free_node(name);
		counter++;
	}
	return (name);
}

int	heredoc_set(t_data *data, t_cmd *cmd, char *limiter)
{
	char	*name;
	pid_t	pid;
	int		i;
	int		status;

	name = heredoc_name();
	cmd->fd[IN] = open(name, O_RDWR | O_CREAT | O_EXCL, 0744);
	if (cmd->fd[IN] < 0)
		return (SUCCESS);
	pid = fork();
	if (pid == 0)
	{
		sig_init(HEREDOC);
		heredoc_write(data, limiter, cmd);
		exit (0);
	}
	sig_init(PARENT_H);
	i = -1;
	waitpid(pid, &status, 0);
	close(cmd->fd[IN]);
	cmd->fd[IN] = open(name, O_RDONLY);
	(unlink(name), sig_init(MAIN));
	if (WIFSIGNALED(status))
		return (data->exit = WTERMSIG(status) + 128, FAILED);
	return (SUCCESS);
}
