/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:43:17 by lefreydier        #+#    #+#             */
/*   Updated: 2023/11/28 19:12:41 by lfreydie         ###   ########.fr       */
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
	t_list **const	garbage = _get_garbage();
	t_list			*node;
	t_list			*cpy;

	if (!ptr || !*garbage)
		return ;
	if ((*garbage)->content == ptr)
	{
		node = (*garbage)->next;
		ft_lstdelone(*garbage, free);
		ptr = NULL;
		*garbage = node;
		return ;
	}
	node = *garbage;
	while (node->next)
	{
		if (node->next->content == ptr)
		{
			cpy = node->next->next;
			ft_lstdelone(node->next, free);
			ptr = NULL;
			node->next = cpy;
			return ;
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
	t_list	*node;
	t_list	*cpy;
	void	*tmp;

	node = (t_list *)_get_garbage();
	while (node)
	{
		cpy = node->next;
		if (node->content != data && !ft_ptreq(data->env, node->content) \
		&& !ft_ptreq(data->grammar, node->content))
		{
			tmp = node->content;
			ft_lstdelone(node, free);
			tmp = NULL;
		}
		node = cpy;
	}
}
