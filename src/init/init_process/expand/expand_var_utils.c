/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blandineberthod <blandineberthod@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:04:38 by blandineber       #+#    #+#             */
/*   Updated: 2023/11/17 15:35:36 by blandineber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**word_split(char *ptr)
{
	char	**ws;
	int		len_ptr;
	int		count;
	int		i;

	i = 0;
	count = 0;
	len_ptr = ft_strlen(ptr);
	while (ptr[i])
	{
		if (ptr[i] == ' ' || ptr[i] == '\t' || ptr[i] == '\n')
			ptr[i] = '\0';
		i++;
	}
	while (i < len_ptr)
	{
		if (!ptr[i] && ptr[i - 1])
			count++;
	}
	ws = gc(ft_calloc(sizeof(char *) * (count + 1)));
	if (!ws)
		exit (1);
	
}
