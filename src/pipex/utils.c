/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:08:25 by lfreydie          #+#    #+#             */
/*   Updated: 2023/05/02 15:57:54 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

t_pipex	*init_struct(int ac, char **av, char **envp)
{
	t_pipex	*infos;

	infos = ft_calloc(sizeof(*infos), 1);
	if (!infos)
		return (ft_exit(NULL, ERR_MAL), NULL);
	infos->ncmd = ac - 3;
	infos->env = envp;
	heredoc_set(infos, av);
	infos->outfile = av[ac - 1];
	parse_cmd(infos, av);
	return (infos);
}

char	**get_paths(t_pipex *infos)
{
	char		*env_path;
	char		**paths;
	int			i;

	i = 0;
	if (!infos->env)
		return (NULL);
	while (infos->env[i])
	{
		env_path = ft_strnstr(infos->env[i], "PATH=", 5);
		if (env_path)
			break ;
		i++;
	}
	if (!env_path)
		ft_exit(infos, NULL);
	paths = ft_split(env_path + 5, ':');
	if (!paths)
		ft_exit(infos, ERR_MAL);
	return (paths);
}

void	parse_cmd(t_pipex *infos, char **av)
{
	int	i;

	infos->tab_cmd = ft_calloc(sizeof(*infos->tab_cmd), infos->ncmd);
	if (!infos->tab_cmd)
	{
		if (infos->heredoc)
			close(infos->tmp_fdin);
		ft_exit(infos, ERR_MAL);
	}
	i = -1;
	while (++i < infos->ncmd)
	{
		infos->tab_cmd[i].cmd = ft_split(av[i + 2 + infos->heredoc], ' ');
		if (!infos->tab_cmd[i].cmd || !(*infos->tab_cmd[i].cmd))
		{
			if (infos->heredoc)
				close(infos->tmp_fdin);
			ft_exit(infos, ERR_MAL);
		}
	}
}

void	heredoc_set(t_pipex *infos, char **av)
{
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		infos->ncmd--;
		if (infos->ncmd < 2)
			ft_exit(infos, ERR_ARG);
		infos->heredoc = 1;
		infos->infile = "heredoc";
		infos->tmp_fdin = open(infos->infile, \
		O_RDWR | O_CREAT | O_EXCL, 0644);
		if (infos->tmp_fdin < 0)
			perror(infos->infile);
		else
		{
			heredoc_write(infos, av[2], "ajout");
			close(infos->tmp_fdin);
		}
	}
	else
		infos->infile = av[1];
}

void	heredoc_write(t_pipex *infos, char *limiter, char *line)
{
	int		i;

	limiter = ft_strjoin(limiter, "\n");
	while (line)
	{
		i = -1;
		while (++i < infos->ncmd - 1)
			write(1, "pipe ", 5);
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
		if (!line)
			(free(limiter), close(infos->tmp_fdin), \
			unlink(infos->infile), ft_exit(infos, NULL));
		if (ft_strncmp(limiter, line, ft_strlen(limiter)))
		{
			write(infos->tmp_fdin, line, ft_strlen(line));
			(free(line), line = "ajout");
		}
		else
		{
			(free(line), free(limiter));
			break ;
		}
	}
}
