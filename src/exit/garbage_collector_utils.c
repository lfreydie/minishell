/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefreydier <lefreydier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:26:16 by lefreydier        #+#    #+#             */
/*   Updated: 2023/11/10 20:07:02 by lefreydier       ###   ########.fr       */
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
	while (tab[i])
	{
		if (tab[i] == ptr)
			return (1);
		i++;
	}
	return (0);
}
