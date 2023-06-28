/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:42:23 by lfreydie          #+#    #+#             */
/*   Updated: 2023/03/07 13:13:05 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*d;
	char	*s;

	i = -1;
	if (!dest && !src)
		n = 0;
	d = (char *)dest;
	s = (char *)src;
	while (&d[i] && &s[i] && ++i < n)
		d[i] = s[i];
	return (dest);
}
/*
int	main (void)
{
	void		*d = NULL;
	const void	*s = NULL;
	size_t		n = 6;

	printf("TEST\n");
	printf("%p \n", ft_memcpy(d, s, n));
	printf("TEST\n");
	printf("%p \n", memcpy(d, s, n));
	printf("TEST\n");
	return (0);
}
*/
