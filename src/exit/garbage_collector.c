/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:43:17 by lefreydier        #+#    #+#             */
/*   Updated: 2023/12/14 19:05:25 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*gc(void *ptr)
{
	t_list	*new;

	if (!ptr)
		err_sys(MALERR);
	new = ft_lstnew(ptr);
	if (!new)
	{
		free(ptr);
		err_sys(MALERR);
	}
	ft_lstadd_back(_get_garbage(), new);
	return (ptr);
}

void	*gc_null(void *ptr)
{
	t_list	*new;

	if (!ptr)
		return (NULL);
	new = ft_lstnew(ptr);
	if (!new)
	{
		free(ptr);
		return (NULL);
	}
	ft_lstadd_back(_get_garbage(), new);
	return (ptr);
}

void	gc_collect(void)
{
	t_list **const	garbage = _get_garbage();
	t_list			*tmp;

	while (*garbage)
	{
		tmp = (*garbage)->next;
		free((*garbage)->content);
		free(*garbage);
		*garbage = tmp;
	}
}
