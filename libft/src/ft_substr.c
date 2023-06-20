/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:21:54 by lfreydie          #+#    #+#             */
/*   Updated: 2023/01/26 12:50:43 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start > slen)
		start = slen;
	if (len > slen - start)
		len = slen - start;
	new = malloc(sizeof(*new) * (len + 1));
	if (!new)
		return (NULL);
	ft_memcpy((void *)new, (const void *)s + start, len);
	new[len] = 0;
	return (new);
}
/*
int	main(int ac, char **av)
{
	char	*new;

	(void)ac;
	new = ft_substr(av[1], (unsigned int)atoi(av[2]), (size_t)atoi(av[3]));
	printf("%s", new);
	return (0);
}
*/
