/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberthod <bberthod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:36:31 by lefreydier        #+#    #+#             */
/*   Updated: 2023/10/23 17:31:14 by bberthod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_write(t_data *data, char *limiter, int fd)
{
	int		i;
	int		flag;
	char	*line;

	(void)data;
	flag = 1;
	limiter = ft_strjoin(limiter, "\n");
	while (flag)
	{
		line = readline("> ");
		if (!line)
		{
			close(fd);
			unlink(fd);
			exit (1);
		}
		if (ft_strncmp(limiter, line, ft_strlen(limiter)))
		{
			write(fd, line, ft_strlen(line));
		}
		else
			flag = 0;
		free(line);
	}
	close(fd);
}

void	heredoc_set(t_data *data, t_cmd *cmd, char *limiter)
{
	int	fd;

	cmd->io_red.heredoc = true;
	cmd->io_red.red_in = "heredoc"; // aleatoire
	fd = open(cmd->io_red.red_in, O_RDWR | O_CREAT | O_EXCL, 0644);
	if (fd < 0)
		exit (1); // code erreur
	heredoc_write(data, limiter, fd);
}
