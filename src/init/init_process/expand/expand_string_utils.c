/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefreydier <lefreydier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:28:35 by lfreydie          #+#    #+#             */
/*   Updated: 2023/11/28 10:37:26 by lefreydier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_new_value(char *ptr, char *var, char *env_val, int i)
{
	int		env_val_len;
	int		var_len;
	char	*new;

	var_len = ft_strlen(var) + 1;
	env_val_len = ft_strlen(env_val);
	new = gc(malloc(sizeof(char) * (ft_strlen(ptr) + env_val_len - var_len)));
	if (!new)
		exit (1);
	ft_memcpy(new, ptr, i);
	ft_memcpy(new + i, env_val, env_val_len);
	ft_memcpy(new + (i + env_val_len), ptr + (i + var_len), \
	ft_strlen(ptr + (i + var_len)) + 1);
	return (new);
}

char	*expand_value(t_data *data, char *var, char *ptr, int i)
{
	char	*env_val;
	char	*new;

	env_val = expand_env_val(data, var);
	new = create_new_value(ptr, var, env_val, i);
	rm_node(env_val);
	rm_node(var);
	rm_node(ptr);
	return (new);
}

char	*rrange_str_join(char *s1, char *s2)
{
	char	*new;

	if (!s1 || !s2)
		exit (1);
	new = gc(ft_strjoin(s1, s2));
	if (!new)
		exit (1);
	rm_node(s1);
	rm_node(s2);
	return (new);
}

char	*rrange_str(t_tok *tk, int start, int end_q)
{
	char	*n_ptr;

	n_ptr = gc(ft_substr(tk->value, start + 1, (end_q - start - 2)));
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
