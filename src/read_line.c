/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blandineberthod <blandineberthod@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 12:12:01 by lefreydier        #+#    #+#             */
/*   Updated: 2023/10/12 15:08:43 by blandineber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_prompt(void)
{
	char	*dir;
	char	*prompt;

	dir = getcwd(NULL, 0);
	if (dir)
	{
		prompt = ft_strjoin(dir, "$ ");
		free(dir);
		return (prompt);
	}
	else
		return (perror("getcwd"), NULL);
}

char *ft_readline() {
    char *line;
    char *prompt;

    prompt = get_prompt();
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, handle_sigquit);
    line = readline(prompt);
    free(prompt);

    if (line == NULL) {
        // Print newline before exiting
        printf("\n");
        exit(0);
    }

    add_history(line);
    return line;
}

// char	*ft_readline(void)
// {
// 	char	*line;
// 	char	*prompt;

// 	prompt = get_prompt();
// 	line = readline(prompt);
// 	free(prompt);
// 	if (line)
// 	{
// 		add_history(line);
// 		return (line);
// 	}
// 	else
// 		return (NULL);
// }
