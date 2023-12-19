/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:52:46 by lefreydier        #+#    #+#             */
/*   Updated: 2023/12/19 10:08:32 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern sig_atomic_t	g_sig;

void	interrupt_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		if (!g_sig)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
	else if (signum == SIGQUIT)
	{
		printf("\nQuit (core dumped)\n");
		// if (!g_sig)
		// {
		// 	rl_on_new_line();
		// 	rl_replace_line("Quit (core dumped)\n", 0);
		// 	rl_redisplay();
		// }
	}
}

void	sig_init(int mode)
{
	g_sig = 0;
	if (mode == MAIN)
	{
		signal(SIGINT, interrupt_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == PARENT)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (mode == HEREDOC)
	{
		signal(SIGINT, interrupt_handler);
		signal(SIGQUIT, SIG_IGN);
	}
}
