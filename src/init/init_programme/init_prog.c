/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:49:12 by lefreydier        #+#    #+#             */
/*   Updated: 2023/12/11 16:48:20 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_prog(t_data *data)
{
	sig_init();
	init_env(data);
	init_grammar(data);
	init_built_gram(data);
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

void	init_built_gram(t_data *data)
{
	data->built_gram[0] = "echo";
	data->built_gram[1] = "cd";
	data->built_gram[2] = "env";
	data->built_gram[3] = "exit";
	data->built_gram[4] = "export";
	data->built_gram[5] = "pwd";
	data->built_gram[6] = "unset";
}
