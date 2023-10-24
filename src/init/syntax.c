/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefreydier <lefreydier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:11:10 by lefreydier        #+#    #+#             */
/*   Updated: 2023/10/24 15:45:12 by lefreydier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_syntax(t_data *data, t_tok *tk, t_tok *prev_tk)
{
	(void)data; // error handles
	if (!prev_tk && tk->op == PIPE)
		exit (1); // code erreur : "bash: syntax error near unexpected token `data->grammar[tk->op]'"
	if (prev_tk && prev_tk->op != NONE && tk->op != NONE)
	{
		if (prev_tk->type == RED_OP && tk->type == CTRL_OP)
			exit (1); // code erreur : "bash: syntax error near unexpected token `data->grammar[tk->op]'"
		else if (prev_tk->type == RED_OP && tk->type == RED_OP)
			exit (1); // code erreur : "bash: syntax error near unexpected token `data->grammar[tk->op]'"
		else if (prev_tk->type == CTRL_OP && tk->type == CTRL_OP)
			exit (1); // code erreur : "bash: syntax error near unexpected token `data->grammar[tk->op]'"
	}
}
