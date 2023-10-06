/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefreydier <lefreydier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:06:38 by bberthod          #+#    #+#             */
/*   Updated: 2023/10/06 17:36:55 by lefreydier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tok	*create_token(void)
{
	t_tok	*new_token;

	new_token = ft_calloc(sizeof(t_tok), 1);
	if (!new_token)
		return (NULL);
	return (new_token);
}

void	add_token(t_data *data, t_tok *token)
{
	t_tok	*current;

	if (data->head == NULL)
	{
		data->head = token;
		data->head->previous = NULL;
	}
	else
	{
		current = data->head;
		while (current->next != NULL)
			current = current->next;
		current->next = token;
		token->previous = current;
	}
	data->num_tokens++;
}

void	print_tokens(t_data *data)
{
	t_tok	*current;
	int		i;
	int		j;

	i = 0;
	current = data->head;
	while (current != NULL)
	{
		printf("Token %d ID: %d\n", i, current->id);
		j = 0;
		while (current->cmd[j] != NULL)
		{
			printf("Command %d: %s\n", j, current->cmd[j]);
			j++;
		}
		if (current->redir_in != NULL)
			printf("Redirection In: %s\n", current->redir_in);
		if (current->redir_out != NULL)
			printf("Redirection Out: %s\n", current->redir_out);
		current = current->next;
		i++;
	}
}

void	print_tokens1(t_data *data)
{
	int	i;

	i = 0;
	while (data->temp->tokens[i] != NULL)
	{
		printf("Token %d : %s\n", i, data->temp->tokens[i]);
		i++;
	}
}
