/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefreydier <lefreydier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:34:44 by lfreydie          #+#    #+#             */
/*   Updated: 2023/11/17 11:13:42 by lefreydier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_string(t_data *data, t_tok *tk, int start)
{
	char	quote;
	char	*ptr;
	int		i;

	i = start;
	ptr = gc(ft_substr(tk->value, start, (ft_strlen(tk->value) - start)));
	if (!ptr)
		exit (1);
	quote = ptr[i++];
	while (ptr[i] != quote)
	{
		if (!ptr[i])
			exit (1); // quote unclose
		if (ptr[i] == '$' && quote == DOUBLE_QUOTE)
			ptr = expand_value(data, find_var(ptr + i + 1), ptr, i);
		else
			i++;
	}
	tk->value = rrange_str(tk, ptr, start, i);
	rm_node(ptr);
}

void	expand_var(t_data *data, t_tok *tk)
{
	char	**ws;

	tk->value = expand_value(data, find_var(tk->value + 1), tk->value, 0);
	ws = word_split(tk->value);

}

t_tok	*expand(t_data *data, t_tok *tk)
{
	int	i;

	i = 0;
	while (!tk->value[i])
	{
		if (tk->value[i] == SINGLE_QUOTE || tk->value[0] == DOUBLE_QUOTE)
			expand_string(data, tk, i);
		else if (tk->value[i] == '$')
			expand_var(data, tk);
	}
	return (tk);
}
