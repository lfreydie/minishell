/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:28:35 by lfreydie          #+#    #+#             */
/*   Updated: 2023/12/21 01:48:39 by lfreydie         ###   ########.fr       */
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
	free_node(s1);
	free_node(s2);
	return (new);
}

char	*expand_value(t_data *data, char *var, char *ptr, int i)
{
	char	*new;
	char	*env_val;
	char	*tmp;
	int		var_len;

	var_len = ft_strlen(var) + 1;
	env_val = expand_env_val(data, var);
	if (i)
	{
		tmp = gc(ft_substr(ptr, 0, i));
		new = rrange_str_join(tmp, env_val);
	}
	else
		new = env_val;
	if (ptr[i + var_len])
	{
		tmp = gc(ft_substr(ptr, i + var_len, \
		ft_strlen(ptr) - (i + var_len)));
		new = rrange_str_join(new, tmp);
	}
	return (new);
}

char	*rrange_str(t_tok *tk, int start, int end_q)
{
	char	*n_ptr;
	char	*tmp;

	n_ptr = gc(ft_substr(tk->value, start + 1, (end_q - start - 1)));
	if (start)
	{
		tmp = gc(ft_substr(tk->value, 0, start));
		n_ptr = rrange_str_join(tmp, n_ptr);
	}
	if (tk->value[end_q + 1])
	{
		tmp = gc(ft_substr(tk->value, end_q + 1, \
		(ft_strlen(tk->value) - end_q)));
		n_ptr = rrange_str_join(n_ptr, tmp);
	}
	free_node(tk->value);
	return (n_ptr);
}
