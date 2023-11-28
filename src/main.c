/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/11/28 20:04:51 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execute.h"

sig_atomic_t	g_sig;

int	main(int ac, char **av)
{
	char	*input;
	t_data	*data;

	(void)av;
	if (ac != 1)
		return (ERROR);
	data = gc(ft_calloc(sizeof(t_data), 1));
	if (!data)
		exit (1); // code erreur
	init_prog(data);
	while (42)
	{
		input = ft_readline();
		if (!input)
			return (printf("exit\n"), 0);
		init_process(data, input);
		// launch_exec_process(data);
		// gc_collect_part(data);
	}
	return (0);
}
