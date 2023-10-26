/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefreydier <lefreydier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/10/26 16:00:55 by lefreydier       ###   ########.fr       */
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
		free_t_data(&data); // free_part(data) -> token + cmd + line + exec
		t_state.signal = 0;
	}
	return (0);
}
