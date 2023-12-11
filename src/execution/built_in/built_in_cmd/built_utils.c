/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:32:27 by lfreydie          #+#    #+#             */
/*   Updated: 2023/12/11 19:01:16 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_table_size(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
		i++;
	return (i);
}

int	ft_strccmp(const char *s1, const char *s2, char c)
{
	unsigned int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while ((s1[i] != c && s2[i] != c) && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	if (s1[i] == c || !s1[i])
		return ('\0' - ((unsigned char *)s2)[i]);
	if (s2[i] == c || !s2[i])
		return (((unsigned char *)s1)[i] - '\0');
	return (0);
}

void	ft_clean_var(char **var)
{
	int		i;
	size_t	size;

	i = 0;
	size = ft_strlen(*var);
	if (ft_sign_append(*var) == FALSE)
		return ;
	while ((*var)[i] != '+')
		i++;
	ft_memmove((*var) + i, (*var) + i + 1, size - (i + 1));
	(*var)[size - 1] = '\0';
}
