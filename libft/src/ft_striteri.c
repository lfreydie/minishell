/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 09:25:01 by lefreydier        #+#    #+#             */
/*   Updated: 2023/01/26 12:50:43 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
/*
void	ft_test(unsigned int i, char *s)
{
	if ((i % 2) == 0)
		s[0] -= 32;
}
*/
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	i = 0;
	if (!s || !f)
		return ;
	while (s[i])
	{
		f((unsigned int)i, s + i);
		i++;
	}
}
/*
int	main(int ac, char **av)
{
	(void)ac;
	ft_striteri(av[1], ft_test);
	printf("%s\n", av[1]);
	return(0);
}
*/
