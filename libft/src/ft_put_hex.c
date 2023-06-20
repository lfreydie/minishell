/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 14:24:08 by lfreydie          #+#    #+#             */
/*   Updated: 2023/01/26 15:31:28 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	put_hex(unsigned int x, char *base)
{
	int	res[100];
	int	i;
	int	len;

	i = 0;
	len = 1;
	while (x >= 16)
	{
		res[i] = base[x % 16];
		x /= 16;
		i++;
		len++;
	}
	res[i] = base[x];
	while (i >= 0)
	{
		ft_putchar(res[i]);
		i--;
	}
	return (len);
}
