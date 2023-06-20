/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:53:21 by lfreydie          #+#    #+#             */
/*   Updated: 2023/01/26 12:50:43 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
		{
			if (((unsigned char)s1[i] - (unsigned char)s2[i]) < -127)
				return (((unsigned char)s1[i] - (unsigned char)s2[i]) * -1);
			else
				return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return (0);
}
/*
int	main(int ac, char **av)
{
	int		size;
	size_t	n;

	size = atoi(av[3]);
	n = (size_t)size;
	(void)ac;
	printf("%d\n", ft_strncmp(av[1], av[2], n));
	return (0);
}
*/
