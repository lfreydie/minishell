/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:10:11 by lefreydier        #+#    #+#             */
/*   Updated: 2023/11/08 15:22:14 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_process(t_data *data, char *input)
{
	data->line = input;
	tokenize_input(data);
	print_token(data);
	parse_token(data);
	print_cmd_list(data);
}

