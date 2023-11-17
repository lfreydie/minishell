/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blandineberthod <blandineberthod@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:34:44 by lfreydie          #+#    #+#             */
/*   Updated: 2023/11/17 15:22:08 by blandineber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_quote(t_data *data, t_tok *tk, int start)
{
	char	quote;
	int		i;

	i = start;
	quote = tk->value[i++];
	while (tk->value[i] != quote)
	{
		if (!tk->value[i])
			exit (1); // quote unclose
		if (tk->value[i] == '$' && quote == DOUBLE_QUOTE)
			tk->value = expand_value(data, find_var(tk->value + i + 1), tk->value, i);
		else
			i++;
	}
	tk->value = rrange_str(tk, start, i);
	return (i - 2);
}

void	expand_var(t_data *data, t_tok *tk, int i)
{
	char	**ws;

	tk->value = expand_value(data, find_var(tk->value[i + 1]), tk->value, i);
	ws = word_split(tk->value + i);
}

t_tok	*expand(t_data *data, t_tok *tk)
{
	int	i;

	i = 0;
	while (!tk->value[i])
	{
		if (tk->value[i] == SINGLE_QUOTE || tk->value[i] == DOUBLE_QUOTE)
			i == expand_quote(data, tk, i);
		else if (tk->value[i] == '$')
			expand_var(data, tk, i);
	}
	return (tk);
}