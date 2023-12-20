/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:15:50 by lefreydier        #+#    #+#             */
/*   Updated: 2023/12/20 23:02:44 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

int	count_word(char *ptr)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (ptr[i])
	{
		if (ft_isspace(ptr[i]))
			i++;
		else
		{
			count++;
			while (ptr[i] && !ft_isspace(ptr[i]))
				i++;
		}
	}
	return (count);
}

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
	else
		return (NULL);
	var = gc(malloc(sizeof(char) * i + 1));
	ft_strlcpy(var, ptr, i + 1);
	return (var);
}

int	find_var_len(char *ptr)
{
	int		count;

	count = 0;
	if (ptr[count] == '?')
		count++;
	else if (ft_isalpha(ptr[count]) || ptr[count] == '_')
	{
		count++;
		while (ft_isalnum(ptr[count]) || ptr[count] == '_')
			count++;
	}
	return (count);
}

void	manage_cmd_null(t_data *data)
{
	t_cmd	*cpy;
	int		j;
	char	**n_cmd;

	cpy = data->lst_cmd;
	while (cpy)
	{
		if (!cpy->value || (!cpy->value[0][0] && cpy->n_args_cmd == 1))
			cpy->launch = FALSE;
		else if (!cpy->value || (!cpy->value[0][0] && cpy->n_args_cmd > 1))
		{
			cpy->n_args_cmd--;
			j = 1;
			n_cmd = gc(ft_calloc(sizeof(char *), cpy->n_args_cmd + 1));
			while (cpy->value && cpy->value[j])
			{
				n_cmd[j - 1] = gc(ft_strdup(cpy->value[j]));
				j++;
			}
			cpy->value = n_cmd;
		}
		if ((cpy->value && cpy->value[0][0]) || cpy->launch == FALSE)
			cpy = cpy->next;
	}
}
