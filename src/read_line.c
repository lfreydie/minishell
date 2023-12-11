/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 12:12:01 by lefreydier        #+#    #+#             */
/*   Updated: 2023/12/11 21:53:48 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_prompt(void)
{
	char	*dir;
	char	*prompt;

	dir = gc(getcwd(NULL, 0));
	if (dir)
	{
		prompt = gc(ft_strjoin(dir, "$ "));
		rm_node(dir);
		return (prompt);
	}
}

char	*ft_readline(void)
{
	char	*line;
	char	*prompt;

	prompt = get_prompt();
	line = gc(readline(prompt));
	rm_node(prompt);
	if (line)
	{
		add_history(line);
		return (line);
	}
}
