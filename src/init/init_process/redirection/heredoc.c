/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:36:31 by lefreydier        #+#    #+#             */
/*   Updated: 2023/12/12 19:22:04 by lfreydie         ###   ########.fr       */
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
			(close(cmd->fd[IN]), err_sys(MALERR));
		if (!ft_streq(line, limiter))
			write(cmd->fd[IN], line, ft_strlen(line));
		else
			flag = 0;
		free_node(line);
	}
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

void	heredoc_set(t_data *data, t_cmd *cmd, char *limiter)
{
	char	*name;

	name = heredoc_name();
	cmd->fd[IN] = open(cmd->io_red->redir, O_RDWR | O_CREAT | O_EXCL, 0744);
	if (cmd->fd[IN] < 0)
		err_sys(PERDEN);
	unlink(name);
	heredoc_write(data, limiter, cmd);
}
