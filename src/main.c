/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 18:07:02 by lfreydie          #+#    #+#             */
/*   Updated: 2023/12/15 18:07:05 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

sig_atomic_t	g_sig;

int	main(int ac, char __attribute__((unused)) **av)
{
	t_data	data;

	if (ac != 1)
		return (printf("Too many arguments\n"), 1);
	sig_init();
	init_env(&data);
	while (42)
	{
		init_prog(&data);
		ft_readline(&data.line);
		if (!data.line)
		{
			printf("exit\n");
			break ;
		}
		if (init_process(&data) == -1)
			continue ;
		launch_exec_process(&data);
	}
	gc_collect();
	return (0);
}
