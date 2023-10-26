/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberthod <bberthod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/10/26 14:32:11 by bberthod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execute.h"

int	main(int ac, char **av)
{
	int		free_flag;
	char	*input;
	t_data	data;

	(void)av;
	if (ac != 1)
		return (ERROR);
	init_prog(&data);
	while (42)
	{
		free_flag = 0;
		input = ft_readline();
		if (!input)
			return (printf("exit\n"), 0);
		init_process(&data, input);
		// launch_exec_process(data);
		free_part(&data);
		free_flag = 1;
		t_state.signal = 0;
	}
	free_t_data(&data, free_flag);
	return (0);
}
