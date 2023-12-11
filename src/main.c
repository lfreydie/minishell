/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/12/11 21:04:07 by lfreydie         ###   ########.fr       */
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
		return (ft_putstr_fd("Too many arguments", STDERR_FILENO), 1);
	ft_bzero(&data, sizeof(t_data));
	init_prog(&data);
	while (42)
	{
		input = ft_readline();
		if (init_process(&data, input) == -1)
		{
			gc_collect_part(&data);
			continue ;
		}
		// launch_exec_process(data);
		// gc_collect_part(data);
	}
	return (0);
}
