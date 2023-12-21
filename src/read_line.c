/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 12:12:01 by lefreydier        #+#    #+#             */
/*   Updated: 2023/12/21 01:02:28 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_prompt(void)
{
	char	*dir;
	char	*prompt;

	dir = gc_null(getcwd(NULL, 0));
	if (!dir)
		dir = getenv("PWD");
	prompt = gc(ft_strjoin(dir, "$ "));
	return (prompt);
}

void	ft_readline(t_data *data, char **line)
{
	char	*prompt;

	prompt = get_prompt();
	*line = gc_null(readline(prompt));
	free_node(prompt);
	if (*line)
		add_history(*line);
	else
		data->exit = 130;
}
