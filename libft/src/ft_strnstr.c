/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:47:08 by lfreydie          #+#    #+#             */
/*   Updated: 2023/01/26 12:50:43 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	len_little;

	i = 0;
	len_little = ft_strlen(little);
	if (!*little)
		return ((char *)big);
	if ((!big && !len) || !*big)
		return (NULL);
	while (i + len_little <= len && big[i])
	{
		if (!ft_memcmp(big + i, little, len_little))
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
	size_t		len;
	const char	*big = NULL;
	const char	*little = "je";

	len = 3;
	printf("TEST \n");
	printf("%s\n", strnstr(big, little, len));
	printf("TEST \n");
	return (0);
}
*/
