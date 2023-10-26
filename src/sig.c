/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefreydier <lefreydier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:52:46 by lefreydier        #+#    #+#             */
/*   Updated: 2023/10/26 15:53:29 by lefreydier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
