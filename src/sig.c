/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:52:46 by lefreydier        #+#    #+#             */
/*   Updated: 2023/12/20 18:58:17 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern sig_atomic_t	g_sig;

void	interrupt_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_putendl_fd("", 2);
		if (!g_sig)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
}

void	parent_handler(int signum)
{
	if (signum == SIGINT)
		ft_putendl_fd("", 2);
	else if (signum == SIGQUIT)
		ft_putendl_fd("Quit (core dumped)", 2);
}

void	heredoc_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_putendl_fd("^C", 2);
		if (!g_sig)
			rl_on_new_line();
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
		signal(SIGINT, parent_handler);
		signal(SIGQUIT, parent_handler);
	}
	else if (mode == CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (mode == HEREDOC)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == PARENT_H)
		(signal(SIGINT, heredoc_handler), signal(SIGQUIT, SIG_IGN));
}
