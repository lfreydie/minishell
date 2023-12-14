/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/12/14 19:45:29 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell.h"

sig_atomic_t	g_sig;

int	main(int ac, char **av)
{
	char	*input;
	t_data	data;

	(void)av;
	if (ac != 1)
		return (printf("Too many arguments\n"), 1);
	sig_init();
	while (42)
	{
		init_prog(&data);
		input = ft_readline();
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (init_process(&data, input) == -1)
			continue ;
		launch_exec_process(&data);
	}
	gc_collect();
	return (0);
}
