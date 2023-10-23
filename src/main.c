/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefreydier <lefreydier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/10/20 18:27:17 by lefreydier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#include "execute.h"

struct						s_state
{
	volatile sig_atomic_t	signal;
}							t_state;

void	interrupt_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		if (!t_state.signal)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_data	*data;

	(void)av;
	if (ac != 1)
		return (ERROR);
	data = ft_calloc(sizeof(t_data), 1);
	data->env = envp;
	t_state.signal = 0;
	signal(SIGINT, interrupt_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		input = ft_readline();
		if (!input)
			return (printf("exit\n"), 0);
		init_process(data, input);
		// launch_exec_process(data);
		free(input); // free_part(data) -> token + cmd + line + exec
		t_state.signal = 0;
	}
	free_all(data);
	return (0);
}
