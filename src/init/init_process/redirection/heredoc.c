/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:36:31 by lefreydier        #+#    #+#             */
/*   Updated: 2023/12/04 18:52:30 by lfreydie         ###   ########.fr       */
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
		line = gc(readline("> "));
		if (!line)
			(close(cmd->fd[IN]), exit (1));
		if (!ft_streq(line, limiter))
			write(cmd->fd[IN], line, ft_strlen(line));
		else
			flag = 0;
		rm_node(line);
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
		if (!count_s)
			exit (1); // code erreur
		name = gc(ft_strjoin("/tmp/heredoc_", count_s));
		if (!name)
			(rm_node(count_s), exit (1)); // code erreur
		rm_node(count_s);
		if (access(name, F_OK))
			break ;
		rm_node(name);
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
		exit (1); // code erreur
	unlink(name);
	heredoc_write(data, limiter, cmd);
}
