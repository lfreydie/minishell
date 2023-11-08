/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:45:42 by bberthod          #+#    #+#             */
/*   Updated: 2023/11/08 15:33:41 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_data *data)
{
	t_tok	*current;

	current = data->lst_tk;
	while (current)
	{
		printf("value = %s, ", current->value);
		printf("op = %d, ", current->op);
		printf("type = %d\n", current->type);
		current = current->next;
	}
}

int	ft_streq(char *str1, char *str2)
{
	int	i;

	i = 0;
	if (!str1)
		return (!str2);
	if (!str2)
		return (0);
	while (str1[i])
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	return (!str2[i]);
}

void	create_close(char *file, int flag, int mode)
{
	int	fd;

	fd = open(file, flag, mode);
	if (fd < 0)
		exit (1); // code erreur
	close(fd);
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
