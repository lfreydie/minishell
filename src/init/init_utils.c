/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberthod <bberthod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:45:42 by bberthod          #+#    #+#             */
/*   Updated: 2023/10/23 17:23:56 by bberthod         ###   ########.fr       */
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

void	print_cmd_list(t_data *data)
{
	t_cmd	*current;
	int		i;

	current = data->lst_cmd;
	while (current)
	{
		printf("Command ID: %d\n", current->id);
		printf("Command Arguments:\n");
		i = 0;
		while (current->cmd_value[i])
		{
			printf("  %s\n", current->cmd_value[i]);
			i++;
		}
		printf("Built-in Command: %s\n", current->built_in ? "Yes" : "No");
		printf("Process ID: %d\n", (int)current->pid);
		printf("Input Redirection: %s\n", current->io_red.red_in);
		printf("Heredoc Input: %s\n", current->io_red.heredoc ? "Yes" : "No");
		printf("Output Redirection: %s\n", current->io_red.red_out);
		printf("Append Output: %s\n", current->io_red.append ? "Yes" : "No");
		printf("\n");
		current = current->next;
	}
}