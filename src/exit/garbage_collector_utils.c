/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:26:16 by lefreydier        #+#    #+#             */
/*   Updated: 2023/12/12 19:48:09 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	**_get_garbage(void)
{
	static t_list	*garbage;

	return (&garbage);
}

int	ft_ptreq(char **tab, void *ptr)
{
	int	i;

	if (tab == ptr)
		return (1);
	i = 0;
	while (tab[i])
	{
		if (tab[i] == ptr)
			return (1);
		i++;
	}
	return (0);
}

void	free_next_node(t_list *cpy)
{
	t_list	*tmp;

	tmp = cpy->next->next;
	free(cpy->next->content);
	free(cpy->next);
	cpy->next = tmp;
}

void	free_node(void *add)
{
	t_list **const	garbage = _get_garbage();
	t_list			*cpy;
	t_list			*node_free;

	if (!add)
		return ;
	if (!*garbage)
		ft_error_msg(NULL, "free_node", NULL, "garbage is empty");
	if ((*garbage)->content == add)
	{
		node_free = (*garbage)->next;
		free((*garbage)->content);
		free(*garbage);
		*garbage = node_free;
		return ;
	}
	cpy = *garbage;
	while (cpy->next)
	{
		if (cpy->next->content == add)
			return (free_next_node(cpy));
		cpy = cpy->next;
	}
}
