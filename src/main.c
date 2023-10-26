/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefreydier <lefreydier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/10/26 16:23:30 by lefreydier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execute.h"

int	main(int ac, char **av)
{
	char	*input;
	t_data	data;

	(void)av;
	if (ac != 1)
		return (ERROR);
	init_prog(&data);
	while (42)
	{
		input = ft_readline();
		if (!input)
			return (printf("exit\n"), 0);
		init_process(&data, input);
		// launch_exec_process(data);
		free(input);
		free_part(&data);
		t_state.signal = 0;
	}
	free_t_data(&data);
	return (0);
}
