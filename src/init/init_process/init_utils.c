/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:45:42 by bberthod          #+#    #+#             */
/*   Updated: 2023/12/12 19:56:48 by lfreydie         ###   ########.fr       */
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
		while (current->value[++i])
			printf("\t%s\n", current->value[i]);
		printf("Built-in: %d\n", current->built_in);
		printf("Launch: %d\n", current->launch);
		while (red != NULL)
		{
			printf("\tRedirection: %s, %d\n", red->redir, red->op);
			red = red->next;
		}
		if (current->next)
			printf("Next Command:");
		printf("\n");
		current = current->next;
	}
}

void	print_gc_count(void)
{
	t_list **const	garbage = _get_garbage();
	t_list			*node;
	int				count;

	count = 0;
	if (!*garbage)
	{
		node = *garbage;
		while (node)
		{
			count++;
			node = node->next;
		}
	}
	printf("number of node : %d\n", count);
}
