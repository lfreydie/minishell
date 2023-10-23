/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberthod <bberthod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:08:37 by bberthod          #+#    #+#             */
/*   Updated: 2023/10/23 12:06:53 by bberthod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*add_cmd(t_data *data)
{
	t_cmd	*new_cmd;
	t_cmd	*last_cmd;

	last_cmd = NULL;
	while ()
}

void	parse_token(t_data *data)
{
	t_cmd	*cmd;
	t_tok	*tk;
	t_tok	*prev_tk;

	tk = data->lst_tk;
	prev_tk = NULL;
	while (tk && tk->op != NWLINE)
	{
		check_syntax(tk, prev_tk);
		if (tk->type == CTRL_OP)
			cmd = add_cmd(data); // ajouter struct cmd
		else if (tk->type == RED_OP)
		{
			add_tk_red(data, tk);
			tk = tk->next;
		}
		else
			add_tk_cmd(data, tk);
		prev_tk = tk;
		tk = tk->next;
	}
}
