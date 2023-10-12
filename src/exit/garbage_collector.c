/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefreydier <lefreydier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:43:17 by lefreydier        #+#    #+#             */
/*   Updated: 2023/10/12 15:12:06 by lefreydier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*gc_calloc(t_data *data, size_t size_of, size_t size)
{
	void	*ptr;
	t_bin	*new;

	ptr = ft_calloc(size_of, size);
	if (ptr)
	{
		new = malloc(sizeof(t_bin));
		if (!new)
		{
			free(ptr);
			return (NULL);
		}
		new->obj = ptr;
		new->next = data->garbage;
		data->garbage = new;
	}
	return (ptr);
}

void	remove_allocation(t_data *data, void *ptr)
{
	t_bin	*current;
	t_bin	*prev;

	prev = NULL;
	current = data->garbage;
	while (current)
	{
		if (current->obj == ptr)
		{
			if (prev == NULL)
				data->garbage = current->next;
			else
				prev->next = current->next;
			free(ptr);
			free(current);
		}
		prev = current;
		current = current->next;
	}
}

void	gc_collect(t_data *data)
{
	t_bin	*next;

	while (data->garbage)
	{
		next = data->garbage->next;
		free(data->garbage->obj);
		free(data->garbage);
		data->garbage = next;
	}
}
