/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefreydier <lefreydier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:32:10 by blandineber       #+#    #+#             */
/*   Updated: 2023/10/26 15:44:47 by lefreydier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_t_tok(t_tok *token)
{
	t_tok	*next;

	while (token)
	{
		next = token->next;
		free(token->value);
		free(token);
		token = next;
	}
}

void	free_t_red(t_red *red)
{
	if (red)
	{
		free(red->red_in);
		free(red->red_out);
	}
}

void	free_t_cmd(t_cmd *command)
{
	t_cmd	*next;
	int		j;

	while (command)
	{
		next = command->next;
		if (command->cmd_value)
		{
			j = -1;
			while (command->cmd_value[++j])
				free(command->cmd_value[j]);
			free(command->cmd_value);
		}
		free_t_red(&command->io_red);
		free(command);
		command = next;
	}
}

void	free_t_data(t_data *data)
{
	if (data)
	{
		free(data->line); // oui
		free(data->env); // non
		free_t_cmd(data->lst_cmd); // oui
		free_t_tok(data->lst_tk); //oui
		free(data->grammar); // non
		free(data); // non
		// num command = 0 et exit flag = ?
	}
}
