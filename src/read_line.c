/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefreydier <lefreydier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 12:12:01 by lefreydier        #+#    #+#             */
/*   Updated: 2023/12/07 16:26:34 by lefreydier       ###   ########.fr       */
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
		if (!prompt)
			exit (1);
		rm_node(dir);
		return (prompt);
	}
	else
		return (perror("getcwd"), NULL);
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
	else
		return (NULL);
}
