/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:47:26 by lfreydie          #+#    #+#             */
/*   Updated: 2023/01/26 12:50:43 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_ischar(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*new;

	if (!s1)
		return (NULL);
	if (!set)
		return ((char *)s1);
	start = 0;
	while (ft_ischar(s1[start], set))
		start += 1;
	end = ft_strlen(s1);
	while (ft_ischar(s1[end - 1], set))
		end -= 1;
	new = ft_substr(s1, (unsigned int)start, end - start);
	return (new);
}
/*
int	main(int ac, char **av)
{
	char	*new;

	(void)ac;
	new = ft_strtrim(av[1], av[2]);
	printf("new : %s\n", new);
}
*/
