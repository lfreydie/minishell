/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:36:00 by lfreydie          #+#    #+#             */
/*   Updated: 2023/01/26 12:50:43 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_is_charset(char a, char c)
{
	if (c == 0)
		return (0);
	if (a == c)
		return (1);
	return (0);
}

int	ft_count_word(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (!ft_is_charset(str[i], c) && str[i])
		{
			count++;
			while (str[i] && !ft_is_charset(str[i], c))
				i ++;
		}
		else if (ft_is_charset(str[i], c) && str[i])
			i++;
	}
	return (count);
}

int	ft_strlen_char(char const *str, char c)
{
	int	i;

	i = 0;
	while (!ft_is_charset(str[i], c) && str[i])
		i ++;
	return (i);
}

int	ft_tab_fill(char const *s, char c, int cc, char **strs)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (ft_is_charset(s[i], c))
		i ++;
	strs[cc] = malloc(sizeof(char) * (ft_strlen_char(s + i, c) + 1));
	if (!strs[cc])
	{
		while (cc >= 0)
			free(strs[cc--]);
		free(strs);
		return (-1);
	}
	while (!ft_is_charset(s[i], c) && s[i])
	{
		strs[cc][j] = s[i];
		i ++;
		j ++;
	}
	strs[cc][j] = 0;
	cc++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		count_words;
	int		cc;
	int		i;

	cc = 0;
	i = 0;
	if (!s)
		return (NULL);
	count_words = ft_count_word(s, c);
	strs = malloc(sizeof(strs) * (count_words + 1));
	if (!strs)
		return (NULL);
	while (cc < count_words)
	{
		i += ft_tab_fill(s + i, c, cc, strs);
		if (i == -1)
			return (NULL);
		cc++;
	}
	strs[cc] = 0;
	return (strs);
}
