/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefreydier <lefreydier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:04:38 by blandineber       #+#    #+#             */
/*   Updated: 2023/11/21 17:05:59 by lefreydier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

int	count_word(char *ptr)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (ptr[i])
	{
		if (ft_isspace(ptr[i]))
			ptr[i++] = '\0';
		else
		{
			count++;
			while (ptr[i] && !ft_isspace(ptr[i]))
				i++;
		}
	}
	return (count);
}

char	**word_split(char *ptr)
{
	char	**ws;
	int		len_ptr;
	int		count;
	int		i;

	len_ptr = ft_strlen(ptr);
	count = count_word(ptr);
	ws = gc(ft_calloc(sizeof(char *), (count + 1)));
	if (!ws)
		exit (1);
	i = 0;
	while (i < count)
	{
		if ()
		ws[i] = ft_strdup(ptr);
	}
}
