/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:11:10 by lefreydier        #+#    #+#             */
/*   Updated: 2023/12/11 21:16:04 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax(t_tok *tk, t_tok *prev_tk)
{
	if (tk->op == PIPE)
	{
		if (!prev_tk)
			return (ft_err_syntax(SHELL, SYNERR, tk->value), FAILED);
		else if (tk->next->type == CTRL_OP)
			return (ft_err_syntax(SHELL, SYNERR, tk->next->value), FAILED);
	}
	if (tk->type == RED_OP && tk->next->type != WORD)
		return (ft_err_syntax(SHELL, SYNERR, tk->next->value), FAILED);
}
