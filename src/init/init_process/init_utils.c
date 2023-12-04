/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:45:42 by bberthod          #+#    #+#             */
/*   Updated: 2023/12/04 19:52:29 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_tok *lst_tk)
{
	t_tok	*current;

	current = lst_tk;
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
	t_red	*red;
	int		i;

	current = data->lst_cmd;
	red = current->io_red;
	while (current != NULL)
	{
		printf("Command ID: %d\n", current->id);
		printf("Command Value:\n");
		i = -1;
		while (current->cmd_value[++i])
			printf("\t%s\n", current->cmd_value[i]);
		printf("Built-in: %d\n", current->built_in);
		printf("Launch: %d\n", current->launch);
		while (red != NULL)
		{
			printf("\tRedirection: %s, %d\n", red->redir, red->op);
			red = red->next;
		}
		printf("Next Command:\n");
		current = current->next;
	}
}

void	print_data(t_data *data)
{
	printf("line = %s\n", (data->line ? "Yes" : "No"));
	printf("cmd = %s\n", (data->lst_cmd ? "Yes" : "No"));
	printf("token = %s\n", (data->lst_tk ? "Yes" : "No"));
	printf("env = %s\n", (data->env ? "Yes" : "No"));
	// printf("grammar = %s\n", (data->grammar ? "Yes" : "No"));
	printf("num cmd = %d\n", data->num_cmd);
	printf("exit flag = %d\n", data->exit_flag);
}
