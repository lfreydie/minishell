/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefreydier <lefreydier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:32:10 by blandineber       #+#    #+#             */
/*   Updated: 2023/10/12 14:42:31 by lefreydier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clear_tokens(t_data *data)
{
	t_tok	*current;
	t_tok	*temp;

	current = data->head;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp->cmd);
		free(temp);
	}
	data->head = NULL;
	data->num_tokens = 0;
}

void	free_all(t_data *data)
{
	free(data->temp->redir);
	free(data->temp->tokens);
	free(data->temp);
}
