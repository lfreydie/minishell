/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberthod <bberthod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/10/26 14:24:08 by bberthod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execute.h"

struct	s_state
{
	volatile sig_atomic_t	signal;
}	t_state;

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

void	sig_init(void)
{
	t_state.signal = 0;
	signal(SIGINT, interrupt_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	init_prog(t_data *data)
{
	sig_init();
	data = ft_calloc(sizeof(t_data), 1);
	if (!data)
		exit (1); // code erreur
	init_env(data);
	init_grammar(data);
}

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
		free_part(&data);
		t_state.signal = 0;
	}
	free_t_data(&data);
	return (0);
}
