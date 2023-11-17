s/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blandineberthod <blandineberthod@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:28:35 by lfreydie          #+#    #+#             */
/*   Updated: 2023/11/17 14:29:54 by blandineber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern sig_atomic_t	g_sig;

char	*find_var(char *ptr)
{
	int		i;
	char	*var;

	i = 0;
	if (ptr[i] == '?')
		i++;
	else if (ft_isalpha(ptr[i]) || ptr[i] == '_')
	{
		i++;
		while (ft_isalnum(ptr[i]) || ptr[i] == '_')
			i++;
	}
	var = gc(malloc(sizeof(char) * i + 1));
	if (!var)
		exit (1); // code erreur
	ft_strlcpy(var, ptr, i + 1);
	return (var);
}

char	*create_new_value(char *ptr, char *var, char *env_val, int i)
{
	int		env_val_len;
	int		var_len;
	char	*new;

	var_len = ft_strlen(var) + 1;
	env_val_len = ft_strlen(env_val);
	new = gc(malloc(sizeof(char) * (ft_strlen(ptr) + env_val_len - var_len)));
	if (!new)
		exit (1); // code erreur
	ft_memcpy(new, ptr, i);
	ft_memcpy(new + i, env_val, env_val_len);
	ft_memcpy(new + (i + env_val_len), ptr + (i + var_len), \
	ft_strlen(ptr + (i + var_len)) + 1);
	rm_node(env_val);
	rm_node(var);
	rm_node(ptr);
	return (new);
}

char	*expand_value(t_data *data, char *var, char *ptr, int i)
{
	int		l;
	int		var_len;
	char	*env_val;
	char	*new;

	env_val = NULL;
	var_len = ft_strlen(var) + 1;
	if (ft_streq("?", var))
		env_val = gc(ft_itoa(g_sig));
	else
	{
		l = -1;
		while (data->env[++l])
		{
			if (!ft_memcmp(var, data->env[l], ft_strlen(var) - 1) \
			&& data->env[l][ft_strlen(var)] == '=')
			{
				env_val = gc(ft_substr(data->env[l], var_len, \
				ft_strlen(data->env[l]) - var_len));
				break ;
			}
		}
	}
	new = create_new_value(ptr, var, env_val, i);
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
