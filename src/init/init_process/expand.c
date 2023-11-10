/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefreydier <lefreydier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:34:44 by lfreydie          #+#    #+#             */
/*   Updated: 2023/11/10 20:23:16 by lefreydier       ###   ########.fr       */
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

t_tok	*expand(t_data *data, t_tok *tk)
{
	char	quote;
	char	*ptr;
	int		i;

	i = 0;
	ptr = tk->value;
	if (ptr[i] == SINGLE_QUOTE || ptr[i] == DOUBLE_QUOTE)
	{
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
		rm_node(ptr);
	}
	return (tk);
}
