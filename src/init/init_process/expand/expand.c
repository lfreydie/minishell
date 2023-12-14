/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:34:44 by lfreydie          #+#    #+#             */
/*   Updated: 2023/12/12 19:35:23 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_quote(t_tok *tk, int start)
{
	char	*var;
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
		{
			var = find_var(tk->value + i + 1);
			tk->value = expand_value(var, tk->value, i);
			i += ft_strlen(expand_env_val(var));
		}
		else
			i++;
	}
	tk->value = rrange_str(tk, start, i);
	return (i - 1);
}

t_tok	*expand_var(t_data *data, t_tok *tk, int i)
{
	t_tok	*n_tk;
	char	**ws;
	char	*ptr;
	char	*var;
	int		var_len;

	var = find_var(tk->value + i + 1);
	ptr = expand_env_val(var);
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
	ws = word_split(ptr, count_word(ptr));
	n_tk = manage_ws(ws, tk, i);
	n_tk = manage_end_ws(data, tk, n_tk, (i + ft_strlen(var)));
	return (n_tk);
}

int	expand_redir(t_data *data, t_red *red)
{
	t_tok	tk;
	t_tok	*tmp_tk;

	tk.value = red->redir;
	tk.type = WORD;
	tk.op = NONE;
	tk.next = NULL;
	tmp_tk = expand(data, &tk, 0);
	if (!tmp_tk->next)
		red->redir = gc(ft_strdup(tmp_tk->value));
	else
		return (0);
	return (1);
}

t_tok	*expand(t_data *data, t_tok *tk, int i)
{
	while (tk->value[i])
	{
		if (tk->value[i] == SINGLE_QUOTE || tk->value[i] == DOUBLE_QUOTE)
			i = expand_quote(tk, i);
		else if (tk->value[i] == '$' && (tk->value[i + 1] && \
		(ft_isalpha(tk->value[i + 1]) || tk->value[i + 1] == '_' || \
		tk->value[i + 1] == SINGLE_QUOTE || tk->value[i + 1] == DOUBLE_QUOTE)))
			tk = expand_var(data, tk, i);
		else
			i++;
	}
	return (tk);
}
