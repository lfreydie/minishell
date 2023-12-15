/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:10:35 by lfreydie          #+#    #+#             */
/*   Updated: 2023/12/15 18:18:18 by lfreydie         ###   ########.fr       */
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
	red->next = NULL;
}

void	manage_redir_out(t_cmd *cmd, t_red *red)
{
	if (cmd->fd[OUT])
		close(cmd->fd[OUT]);
	if (red->op == OUTAP_RED)
		cmd->fd[OUT] = open(red->redir, \
		O_RDWR | O_CREAT | O_APPEND, 0644);
	else if (red->op == OUTTR_RED)
		cmd->fd[OUT] = open(red->redir, \
		O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (cmd->fd[OUT] < 0)
	{
		cmd->launch = false;
		ft_error_msg(SHELL, red->redir, NULL, NOFLDIR);
	}
	printf("redir : %d\n", cmd->fd[OUT]);
}

void	manage_redir_in(t_data *data, t_cmd *cmd, t_red *red)
{
	if (cmd->fd[IN])
		close(cmd->fd[IN]);
	if (red->op == HEREDOC_RED)
		heredoc_set(data, cmd, red->redir);
	else if (red->op == IN_RED)
		cmd->fd[IN] = open(red->redir, O_RDONLY);
	if (cmd->fd[IN] < 0)
	{
		cmd->launch = false;
		ft_error_msg(SHELL, red->redir, NULL, NOFLDIR);
	}
	printf("redir : %d\n", cmd->fd[OUT]);
}

void	manage_redir(t_data *data)
{
	t_cmd	*l_cmd;
	t_red	*l_red;

	l_cmd = data->lst_cmd;
	while (l_cmd)
	{
		l_red = l_cmd->io_red;
		while (l_red && l_cmd->launch)
		{
			printf("REDIRECTION\n");
			if (!expand_redir(data, l_red))
				l_cmd->launch = false;
			if ((l_red->op == HEREDOC_RED) || (l_red->op == IN_RED))
				manage_redir_in(data, l_cmd, l_red);
			else if ((l_red->op == OUTAP_RED) || (l_red->op == OUTTR_RED))
				manage_redir_out(l_cmd, l_red);
			l_red = l_red->next;
		}
		l_cmd = l_cmd->next;
	}
}
