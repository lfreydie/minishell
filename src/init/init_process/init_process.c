/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:10:11 by lefreydier        #+#    #+#             */
/*   Updated: 2023/11/29 17:16:23 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_process(t_data *data, char *input)
{
	data->line = input;
	tokenize_input(data);
	print_token(data->lst_tk);
	parse_token(data);
	print_cmd_list(data);
}

