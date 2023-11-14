/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:26:16 by lefreydier        #+#    #+#             */
/*   Updated: 2023/11/14 16:21:27 by lfreydie         ###   ########.fr       */
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
