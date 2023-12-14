/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 12:12:01 by lefreydier        #+#    #+#             */
/*   Updated: 2023/12/14 19:46:49 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_prompt(void)
{
	char	*dir;
	char	*prompt;

	dir = gc(getcwd(NULL, 0));
	prompt = gc(ft_strjoin(dir, "$ "));
	free_node(dir);
	return (prompt);
}

char	*ft_readline(void)
{
	char	*line;
	char	*prompt;

	prompt = get_prompt();
	line = gc_null(readline(prompt));
	free_node(prompt);
	if (line)
		add_history(line);
	if (!line)
		printf("HERE\n");
	return (line);
}
