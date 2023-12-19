/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:49:12 by lefreydier        #+#    #+#             */
/*   Updated: 2023/12/19 10:00:03 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_prog(t_data *data)
{
	sig_init(MAIN);
	data->line = NULL;
	data->lst_cmd = NULL;
	data->lst_tk = NULL;
	data->num_cmd = 0;
	data->tmp_fdin = -1;
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

// void	init_built_gram(t_data *data)
// {
// 	data->built_gram[0] = "echo";
// 	data->built_gram[1] = "echo ";
// 	data->built_gram[2] = "cd";
// 	data->built_gram[3] = "cd ";
// 	data->built_gram[4] = "env";
// 	data->built_gram[5] = "env ";
// 	data->built_gram[6] = "exit";
// 	data->built_gram[7] = "exit ";
// 	data->built_gram[8] = "export";
// 	data->built_gram[9] = "export ";
// 	data->built_gram[10] = "pwd";
// 	data->built_gram[11] = "pwd ";
// 	data->built_gram[12] = "unset";
// 	data->built_gram[13] = "unset ";
// }

void	init_built_gram(t_data *data)
{
	data->built_gram[0] = "echo";
	data->built_gram[1] = "echo ";
	data->built_gram[2] = "cd";
	data->built_gram[3] = "cd ";
	data->built_gram[4] = "pwd";
	data->built_gram[5] = "pwd ";
	data->built_gram[6] = "export";
	data->built_gram[7] = "export ";
	data->built_gram[8] = "unset";
	data->built_gram[9] = "unset ";
	data->built_gram[10] = "env";
	data->built_gram[11] = "env ";
	data->built_gram[12] = "exit";
	data->built_gram[13] = "exit ";
}
