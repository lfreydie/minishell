/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefreydier <lefreydier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:11:10 by lefreydier        #+#    #+#             */
/*   Updated: 2023/10/23 14:29:24 by lefreydier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_syntax(t_data *data, t_tok *tk, t_tok *prev_tk)
{
	(void)data; // sortie erreur
	if (!prev_tk && tk->op == PIPE)
		exit (1); // code erreur : "bash: syntax error near unexpected token `data->grammar[tk->op]'"
	if (prev_tk->op != NONE && tk->op != NONE)
		exit (1); // code erreur : "bash: syntax error near unexpected token `data->grammar[tk->op]'"
}
