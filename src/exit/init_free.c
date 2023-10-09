/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blandineberthod <blandineberthod@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:32:10 by blandineber       #+#    #+#             */
/*   Updated: 2023/10/09 16:25:25 by blandineber      ###   ########.fr       */
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

void	init_data(t_data *data)
{
	data->exit_flag = 0;
	data->temp = (t_temp *)malloc(sizeof(t_temp));
	data->temp->tokens = NULL;
	data->temp->redir = NULL;
	data->head = NULL;
	data->num_tokens = 0;
}

void	free_all(t_data *data)
{
	free(data->temp->redir);
	free(data->temp->tokens);
	free(data->temp);
}

