/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefreydier <lefreydier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:19:29 by lefreydier        #+#    #+#             */
/*   Updated: 2023/10/20 18:33:55 by lefreydier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_data *data)
{
	t_tok	*current;

	current = data->lst_tk;
	while (current)
	{
		printf("value = '%s'\n", current->value);
		printf("op = '%d'\n", current->op);
		printf("type = '%d'\n", current->type);
		current = current->next;
	}
}
