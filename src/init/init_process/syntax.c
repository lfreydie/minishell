/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:11:10 by lefreydier        #+#    #+#             */
/*   Updated: 2023/11/15 16:49:53 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_syntax(t_data *data, t_tok *tk, t_tok *prev_tk)
{
	(void)data; // error handles
	if (tk->op == PIPE)
	{
		if (!prev_tk)
			exit (1);
		else if (!tk->next || tk->next->type == CTRL_OP)
			exit (1);
	}
	if (tk->type == RED_OP && (!tk->next || tk->next->type != WORD))
		exit (1);
}
