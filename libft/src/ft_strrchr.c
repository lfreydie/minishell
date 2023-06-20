/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:44:40 by lfreydie          #+#    #+#             */
/*   Updated: 2023/01/26 15:34:06 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned int	i;
	int				adr;

	i = 0;
	adr = -1;
	while (s[i])
	{
		if (s[i] == (char)c)
			adr = i;
		i++;
	}
	if ((char)c == s[i])
		adr = i;
	if (adr != -1)
		return ((char *)s + adr);
	return (NULL);
}
