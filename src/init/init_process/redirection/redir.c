/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:10:35 by lfreydie          #+#    #+#             */
/*   Updated: 2023/12/20 22:55:03 by lfreydie         ###   ########.fr       */
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

void	manage_redir_out(t_data *data, t_cmd *cmd, t_red *red)
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
		cmd->launch = FALSE;
		data->exit = 1;
		ft_error_msg(SHELL, red->redir, NULL, PERDEN);
	}
}

int	manage_redir_in(t_data *data, t_cmd *cmd, t_red *red)
{
	if (cmd->fd[IN] > 0)
		close(cmd->fd[IN]);
	if (red->op == HEREDOC_RED)
	{
		if (heredoc_set(data, cmd, red->redir) == FAILED)
			return (FAILED);
	}
	else if (red->op == IN_RED)
		cmd->fd[IN] = open(red->redir, O_RDONLY);
	if (cmd->fd[IN] < 0)
	{
		cmd->launch = FALSE;
		data->exit = 1;
		ft_error_msg(SHELL, red->redir, NULL, NOFLDIR);
	}
	return (SUCCESS);
}

int	manage_redir(t_data *data)
{
	t_cmd	*l_cmd;
	t_red	*l_red;

	l_cmd = data->lst_cmd;
	while (l_cmd)
	{
		l_red = l_cmd->io_red;
		while (l_red && l_cmd->launch == TRUE)
		{
			if (!expand_redir(data, l_red))
				l_cmd->launch = FALSE;
			if ((l_red->op == HEREDOC_RED) || (l_red->op == IN_RED))
			{
				if (manage_redir_in(data, l_cmd, l_red) == FAILED)
					return (FAILED);
			}
			else if ((l_red->op == OUTAP_RED) || (l_red->op == OUTTR_RED))
				manage_redir_out(data, l_cmd, l_red);
			l_red = l_red->next;
		}
		l_cmd = l_cmd->next;
	}
	return (SUCCESS);
}
