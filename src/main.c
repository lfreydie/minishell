/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 16:28:11 by lfreydie          #+#    #+#             */
/*   Updated: 2023/06/29 14:39:44 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av)
{
	char	*line;

	(void)av;
	if (ac != 1)
		return (EXIT_FAILURE);
	// config_struct_gen();
	while (1)
	{
		line = ft_readline();
		if (!line)
			break ;
		config_line_store(line);
		ft_printf("input = %s\n", line);
		free(line);
		// exec_line(line);
	}
}
