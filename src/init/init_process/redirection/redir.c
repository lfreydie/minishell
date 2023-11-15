/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:10:35 by lfreydie          #+#    #+#             */
/*   Updated: 2023/11/15 16:54:27 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_red	*lstadd_red(t_cmd *cmd)
{
	t_red	*n_red;
	t_red	*l_red;

	l_red = cmd->io_red;
	while (l_red && l_red->next)
		l_red = l_red->next;
	n_red = gc(ft_calloc(sizeof(t_red), 1));
	if (!n_red)
		exit (1);
	if (!l_red)
		cmd->io_red = n_red;
	else
		l_red->next = n_red;
	return (n_red);
}

void	add_red(t_red *red, t_tok *tk)
{
	red->op = tk->op;
	red->redir = tk->next->value;
}
