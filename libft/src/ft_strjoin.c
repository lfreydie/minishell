/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:36:30 by lfreydie          #+#    #+#             */
/*   Updated: 2023/01/26 12:50:43 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*new;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	new = malloc(sizeof(*new) * (len_s1 + len_s2 + 1));
	if (!new)
		return (NULL);
	ft_memcpy((void *)new, (const void *)s1, len_s1);
	ft_memcpy((void *)new + len_s1, (const void *)s2, len_s2);
	new[len_s1 + len_s2] = 0;
	return (new);
}
/*
int	main(int ac, char **av)
{
	char	*new;

	(void)ac;
	new = ft_strjoin(av[1], av[2]);
	puts(new);
}
*/
