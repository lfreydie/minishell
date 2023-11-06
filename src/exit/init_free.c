/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:32:10 by blandineber       #+#    #+#             */
/*   Updated: 2023/11/06 17:11:22 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	free_part(t_data *data)
{
	if (data)
	{
		free(data->line);
		free_t_cmd(data->lst_cmd);
		free_t_tok(data->lst_tk);
		data->num_cmd = 0;
	}
}

void	free_t_data(t_data *data, int free_flag)
{
	if (data)
	{
		if (free_flag == 0)
			free_part(data);
		free(data->env);
		free(data->grammar);
		free(data);
	}
}

