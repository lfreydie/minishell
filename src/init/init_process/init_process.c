/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:10:11 by lefreydier        #+#    #+#             */
/*   Updated: 2023/12/21 01:20:32 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_process(t_data *data)
{
	if (tokenize_input(data) == FAILED)
		return (FAILED);
	if (parse_token(data) == FAILED)
		return (FAILED);
	if (manage_redir(data) == FAILED)
		return (FAILED);
	manage_cmd_null(data);
	return (SUCCESS);
}
