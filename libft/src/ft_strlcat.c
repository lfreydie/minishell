/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 10:42:33 by lfreydie          #+#    #+#             */
/*   Updated: 2023/01/26 12:50:43 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len_d;
	size_t	len_s;

	i = 0;
	if (!size)
		return (ft_strlen(src));
	len_d = ft_strlen(dst);
	len_s = ft_strlen(src);
	if (size < len_d)
		return (len_s + size);
	while (len_d + i < size - 1 && src[i])
	{
		dst[len_d + i] = src[i];
		i ++;
	}
	dst[len_d + i] = 0;
	return (len_d + len_s);
}
/*
int	main(int ac, char **av)
{
	(void)ac;
	printf("%ld\n", ft_strlcat(av[1], av[2], atoi(av[3])));
	puts(av[1]);
	return (0);
}
*/
