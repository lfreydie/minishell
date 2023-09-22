/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberthod <bberthod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:06:38 by bberthod          #+#    #+#             */
/*   Updated: 2023/09/22 17:38:14 by bberthod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strtok(char *str, const char *delimiters)
{
	static char	*next_token;
	char		*token;

	if (str != NULL)
		next_token = str;
	if (next_token == NULL)
		return (NULL);
	while (*next_token != '\0' && ft_strchr(delimiters, *next_token))
		next_token++;
	if (*next_token == '\0')
		return (next_token = NULL, NULL);
	token = next_token;
	while (*next_token != '\0' && !strchr(delimiters, *next_token))
		next_token++;
	if (*next_token != '\0')
	{
		*next_token = '\0';
		next_token++;
	}
	else
		next_token = NULL;
	return (token);
}
