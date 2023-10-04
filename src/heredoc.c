/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefreydier <lefreydier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 14:13:04 by lfreydie          #+#    #+#             */
/*   Updated: 2023/10/04 12:35:41 by lefreydier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"


// void	heredoc_set(t_pipex *infos, char **av)
// {
// 	if (ft_strncmp(av[1], "here_doc", 8) == 0)
// 	{
// 		infos->ncmd--;
// 		if (infos->ncmd < 2)
// 			ft_exit(infos, ERR_ARG);
// 		infos->heredoc = 1;
// 		infos->infile = "heredoc"; // nom de fichier qui s'incremente ou aleatoire
// 		infos->tmp_fdin = open(infos->infile, O_RDWR | O_CREAT | O_EXCL, 0644);
// 		if (infos->tmp_fdin < 0)
// 			perror(infos->infile);
// 		else
// 		{
// 			heredoc_write(infos, av[2], "ajout");
// 			close(infos->tmp_fdin);
// 		}
// 	}
// 	else
// 		infos->infile = av[1];
// }

// void	heredoc_write(t_pipex *infos, char *limiter, char *line)
// {
// 	int		i;

// 	limiter = ft_strjoin(limiter, "\n");
// 	while (line)
// 	{
// 		i = -1;
// 		while (++i < infos->ncmd - 1)
// 			write(1, "pipe ", 5);
// 		write(1, "heredoc> ", 9);
// 		line = get_next_line(0);
// 		if (!line)
// 			(free(limiter), close(infos->tmp_fdin), unlink(infos->infile), ft_exit(infos, NULL));
// 		if (ft_strncmp(limiter, line, ft_strlen(limiter)))
// 		{
// 			write(infos->tmp_fdin, line, ft_strlen(line));
// 			(free(line), line = "ajout");
// 		}
// 		else
// 		{
// 			(free(line), free(limiter));
// 			break ;
// 		}
// 	}
// }

