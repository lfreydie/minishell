/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:36:31 by lefreydier        #+#    #+#             */
/*   Updated: 2023/11/15 15:15:38 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_write(t_data *data, char *limiter, int fd, char *filename)
{
	int		flag;
	char	*line;

	(void)data;
	flag = 1;
	while (flag)
	{
		line = gc(readline("> "));
		if (!line)
			(close(fd), unlink(filename), exit (1));
		if (!ft_streq(line, limiter))
			write(fd, line, ft_strlen(line));
		else
			flag = 0;
		rm_node(line);
	}
	close(fd);
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

void	heredoc_set(t_data *data, t_cmd *cmd, t_tok *tk, char *limiter)
{
	int		fd;

	check_syntax(data, tk, tk->next);
	cmd->io_red.heredoc = true;
	cmd->io_red.red_in = heredoc_name();
	fd = open(cmd->io_red.red_in, O_RDWR | O_CREAT | O_EXCL, 0744);
	if (fd < 0)
		exit (1); // code erreur
	heredoc_write(data, limiter, fd, cmd->io_red.red_in);
}
