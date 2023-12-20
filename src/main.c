/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 18:07:02 by lfreydie          #+#    #+#             */
/*   Updated: 2023/12/20 18:52:00 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

sig_atomic_t	g_sig;

int	is_only_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int	main(int ac, char __attribute__((unused)) **av)
{
	t_data	data;

	if (ac != 1)
		return (printf("Too many arguments\n"), 1);
	init_env(&data);
	data.exit = 0;
	while (42)
	{
		init_prog(&data);
		ft_readline(&data.line);
		if (!data.line)
		{
			printf("exit\n");
			break ;
		}
		if (is_only_space(data.line))
			continue ;
		if (init_process(&data) == FAILED)
			continue ;
		sig_init(MAIN);
		launch_exec_process(&data);
	}
	gc_collect();
	return (0);
}
