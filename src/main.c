/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 16:28:11 by lfreydie          #+#    #+#             */
/*   Updated: 2023/06/28 18:32:45 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char	*line;

	config_struct_gen();
	while (1)
	{
		line = ft_readline();
		if (!line)
			break ;
		parsing_line(line);
		ft_printf("input = %s\n", line);
		free(line);
		// init_line(line);
		// exec_line(line);
	}
}
