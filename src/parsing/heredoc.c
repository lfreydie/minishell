/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefreydier <lefreydier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 14:13:04 by lfreydie          #+#    #+#             */
/*   Updated: 2023/10/06 17:48:52 by lefreydier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_set(t_tok *token, char *limiter)
{
	int	fd;

	token->heredoc = true;
	token->redir_in = "heredoc"; // nom de fichier qui s'incremente ou aleatoire
	fd = open(token->redir_in, O_RDWR | O_CREAT | O_EXCL, 0644);
	if (fd < 0)
		perror(ERR_NOP);
	else
	{
		heredoc_write(token, limiter, fd);
		close(fd);
	}
}

void	heredoc_write(t_tok *token, char *limiter, int fd)
{
	bool	stop;
	char	*line;

	stop = false;
	limiter = ft_strjoin(limiter, "\n");
	while (!stop)
	{
		line = readline("> ");
		if (!line)
			(close(fd), unlink(token->redir_in), exit(1)); // code erreur
		if (ft_strncmp(limiter, line, ft_strlen(limiter)))
			write(fd, line, ft_strlen(line));
		else
			stop = true;
		free(line);
	}
}

