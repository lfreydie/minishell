/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:11:10 by lefreydier        #+#    #+#             */
/*   Updated: 2023/12/20 18:58:38 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax(t_data *data, t_tok *tk, t_tok *prev_tk)
{
	if (tk->op == PIPE)
	{
		if (!prev_tk)
			return (ft_err_syntax(data, SHELL, SYNERR, tk->value), FAILED);
		else if (tk->next->type == CTRL_OP)
			return (ft_err_syntax(data, SHELL, SYNERR, \
			tk->next->value), FAILED);
	}
	if (tk->type == RED_OP && tk->next->type != WORD)
		return (ft_err_syntax(data, SHELL, SYNERR, tk->next->value), FAILED);
	return (SUCCESS);
}
