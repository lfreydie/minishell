/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:34:44 by lfreydie          #+#    #+#             */
/*   Updated: 2023/11/15 18:45:56 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_string(t_data *data, t_tok *tk)
{
	char	quote;
	char	*ptr;
	int		i;

	i = 0;
	ptr = tk->value;
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
	tk->value = gc(ft_substr(ptr, 1, (ft_strlen(ptr) - 2)));
	// rm quote (str doesn't always begin at quote)
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
			expand_string(data, tk);
		else if (ptr[i] == '$')
			expand_var(data, tk, cmd);
	}
	return (tk);
}
