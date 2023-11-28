/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:28:35 by lfreydie          #+#    #+#             */
/*   Updated: 2023/11/28 21:09:31 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*rrange_str_join(char *s1, char *s2)
{
	char	*new;

	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	new = gc(ft_strjoin(s1, s2));
	if (!new)
		exit (1);
	rm_node(s1);
	rm_node(s2);
	return (new);
}

char	*expand_value(t_data *data, char *var, char *ptr, int i)
{
	char	*new;
	char	*env_val;
	int		var_len;

	var_len = ft_strlen(var) + 1;
	env_val = expand_env_val(data, var);
	if (i)
		new = rrange_str_join(gc(ft_substr(ptr, 0, i)), env_val);
	else
		new = env_val;
	if (ptr[i + var_len])
		new = rrange_str_join(new, gc(ft_substr(ptr, i + var_len, \
		ft_strlen(ptr) - (i + var_len))));
	return (new);
}

char	*rrange_str(t_tok *tk, int start, int end_q)
{
	char	*n_ptr;

	n_ptr = gc(ft_substr(tk->value, start + 1, (end_q - start - 1)));
	if (!n_ptr)
		exit (1);
	if (start)
		n_ptr = rrange_str_join(gc(ft_substr(tk->value, 0, start)), n_ptr);
	if (tk->value[end_q + 1])
		n_ptr = rrange_str_join(n_ptr, gc(ft_substr(tk->value, end_q + 1, \
		(ft_strlen(tk->value) - end_q))));
	rm_node(tk->value);
	return (n_ptr);
}
