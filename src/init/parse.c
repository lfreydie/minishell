/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberthod <bberthod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:08:37 by bberthod          #+#    #+#             */
/*   Updated: 2023/10/23 14:07:54 by bberthod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*add_cmd(t_data *data)
{
	t_cmd	*new_cmd;
	t_cmd	*last_cmd;

	last_cmd = data->lst_cmd;
	while (last_cmd && last_cmd->next)
		last_cmd = last_cmd->next;
	new_cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!new_cmd)
		exit(1); // code erreur
	if (!last_cmd)
		data->lst_cmd = new_cmd;
	else
		last_cmd->next = new_cmd;
	return (new_cmd);
}

void	add_tk_red(t_data *data, t_tok	*tk, t_cmd *cmd)
{
	int	fd;

	if (tk->op == IN_RED || tk->op == HEREDOC_RED)
	{
		if (cmd->io_red.red_in)
			(fd = open(cmd->io_red.red_in, O_RDONLY), close(fd));
		if (tk->op == IN_RED)
		{
			cmd->io_red.red_in = tk->next->value;
			cmd->io_red.heredoc = false;
		}
		else
			heredoc_set(data, tk->next->value);
	}
	else if (tk->op == OUTTR_RED || tk->op == OUTAP_RED)
	{
		if (cmd->io_red.red_out)
			(fd = open(cmd->io_red.red_out, O_RDONLY), close(fd));
		if (tk->op == OUTAP_RED)
			cmd->io_red.append = true;
		else
			cmd->io_red.append = false;
		cmd->io_red.red_out = tk->next->value;
	}
}

void	add_tk_cmd(t_data *data, t_tok *tk, int i)
{
	int	id;

	id = data->lst_cmd->id;
	if (tk->type == WORD)
		data->lst_cmd->cmd[id][i] = tk->value;
}

void	parse_token(t_data *data)
{
	t_cmd	*cmd;
	t_tok	*tk;
	t_tok	*prev_tk;
	int		i;

	i = 0;
	tk = data->lst_tk;
	prev_tk = NULL;
	while (tk && tk->op != NWLINE)
	{
		check_syntax(tk, prev_tk);
		if (tk->type == CTRL_OP)
			cmd = add_cmd(data); // ajouter struct cmd
		else if (tk->type == RED_OP)
		{
			add_tk_red(data, tk, cmd);
			tk = tk->next;
		}
		else
		{
			add_tk_cmd(data, tk, i);
			i++;
		}
		prev_tk = tk;
		tk = tk->next;
	}
}
