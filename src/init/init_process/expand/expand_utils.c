/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:15:50 by lefreydier        #+#    #+#             */
/*   Updated: 2023/11/28 20:24:57 by lfreydie         ###   ########.fr       */
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

char	*find_var(char *ptr)
{
	int		i;
	char	*var;

	i = 0;
	if (ptr[i] == '?')
		i++;
	else if (ft_isalpha(ptr[i]) || ptr[i] == '_')
	{
		i++;
		while (ft_isalnum(ptr[i]) || ptr[i] == '_')
			i++;
	}
	var = gc(malloc(sizeof(char) * i + 1));
	if (!var)
		exit (1); // code erreur
	ft_strlcpy(var, ptr, i + 1);
	return (var);
}

int	find_var_len(char *ptr)
{
	int		count;

	count = 0;
	if (ptr[count] == '?')
		count++;
	else if (ft_isalpha(ptr[count]) || ptr[count] == '_')
	{
		count++;
		while (ft_isalnum(ptr[count]) || ptr[count] == '_')
			count++;
	}
	return (count);
}
