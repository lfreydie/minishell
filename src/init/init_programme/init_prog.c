/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:49:12 by lefreydier        #+#    #+#             */
/*   Updated: 2023/11/29 18:41:40 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_prog(t_data *data)
{
	sig_init();
	init_env(data);
	init_grammar(data);
}

void	init_grammar(t_data *data)
{
	data->grammar[0] = MUCH_LESS;
	data->grammar[1] = LESS;
	data->grammar[2] = MUCH_MORE;
	data->grammar[3] = MORE;
	data->grammar[4] = BAR;
	data->grammar[5] = S_NEWLINE;
}
