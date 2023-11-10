/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefreydier <lefreydier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:43:17 by lefreydier        #+#    #+#             */
/*   Updated: 2023/11/10 17:30:31 by lefreydier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*gc(void *ptr)
{
	t_list	*new;

	if (!ptr)
		exit (1);
	new = ft_lstnew(ptr);
	if (!new)
	{
		free(ptr);
		return (NULL);
	}
	ft_lstadd_back(_get_garbage(), new);
	return (ptr);
}

void	rm_node(void *ptr)
{
	t_list	**garbage;
	t_list	*node;
	t_list	*cpy;

	garbage = _get_garbage();
	if ((*garbage)->content == ptr)
	{
		node = (*garbage)->next;
		ft_lstdelone((*garbage), free);
		(*garbage) = node;
	}
	node = (*garbage);
	while (node)
	{
		if (node->next->content == ptr)
		{
			cpy = node->next->next;
			ft_lstdelone(node->next, free);
			node->next = cpy;
		}
		node = node->next;
	}
}

void	gc_collect(void)
{
	t_list	**garbage;
	t_list	*node;

	garbage = _get_garbage();
	while (*garbage)
	{
		node = (*garbage)->next;
		ft_lstdelone((*garbage), free);
		(*garbage) = node;
	}
}

void	gc_collect_part(t_data *data)
{
	t_list	**garbage;
	t_list	*node;
	t_list	*cpy;

	garbage = _get_garbage();
	node = (*garbage);
	while (node)
	{
		cpy = node->next;
		if (node->content != data || !ft_ptreq(data->env, node->content) \
		|| !ft_ptreq(data->grammar, node->content))
			ft_lstdelone(node, free);
		node = cpy;
	}
}
