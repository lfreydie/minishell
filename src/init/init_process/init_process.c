/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:10:11 by lefreydier        #+#    #+#             */
/*   Updated: 2023/12/14 19:34:53 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_process(t_data *data, char *input)
{
	data->line = input;
	if (tokenize_input(data) == -1)
		return (FAILED);
	// print_token(data->lst_tk);
	if (parse_token(data) == -1)
		return (FAILED);
	manage_redir(data);
	// print_cmd_list(data);
	return (SUCCESS);
}

