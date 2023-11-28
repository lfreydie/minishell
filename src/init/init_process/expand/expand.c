/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:34:44 by lfreydie          #+#    #+#             */
/*   Updated: 2023/11/28 21:28:43 by lfreydie         ###   ########.fr       */
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
			exit (1);
		if (tk->value[i] == '$' && quote == DOUBLE_QUOTE \
		&& (ft_isalpha(tk->value[i + 1]) || tk->value[i + 1] == '_'))
			tk->value = expand_value(data, \
			find_var(tk->value + i + 1), tk->value, i);
		else
			i++;
	}
	tk->value = rrange_str(tk, start, i);
	return (i - 2);
}

t_tok	*expand_var(t_data *data, t_tok *tk, t_tok *prev_tk, int i)
{
	char	**ws;
	char	*ptr;
	char	*var;
	int		var_len;

	var = find_var(tk->value + i + 1);
	ptr = expand_env_val(data, var);
	if (!ptr)
	{
		var_len = ft_strlen(var);
		if (i)
			ptr = gc(ft_substr(tk->value, 0, i));
		if (tk->value[i + var_len + 1])
			tk->value = rrange_str_join(ptr, gc(ft_substr(tk->value, i + \
			var_len + 1, (ft_strlen(tk->value) - (i + var_len + 1)))));
		return (tk);
	}
	ws = word_split(ptr);
	printf("HERE\n");
	tk = manage_ws(ws, tk, var, i);
	printf("HERE\n");
	if (prev_tk)
		prev_tk->next = tk;
	else
		data->lst_tk = tk;
	return (tk);
}

t_tok	*expand(t_data *data, t_tok *tk, t_tok *prev_tk)
{
	int	i;

	i = 0;
	while (tk->value[i])
	{
		if (tk->value[i] == SINGLE_QUOTE || tk->value[i] == DOUBLE_QUOTE)
			i = expand_quote(data, tk, i);
		else if (tk->value[i] == '$' && \
		(ft_isalpha(tk->value[i + 1]) || tk->value[i + 1] == '_'))
			tk = expand_var(data, tk, prev_tk, i);
		else
			i++;
	}
	return (tk);
}
