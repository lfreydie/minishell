/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefreydier <lefreydier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:05:05 by lefreydier        #+#    #+#             */
/*   Updated: 2023/11/17 11:30:04 by lefreydier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*rrange_str(t_tok *tk, char *ptr, int start, int end_q)
{
	char	*n_ptr_1;
	char	*n_ptr_2;
	char	*n_ptr_3;

	n_ptr_1 = gc(ft_substr(ptr, start + 1, (end_q - start - 2)));
	if (start)
	{
		n_ptr_2 = gc(ft_substr(tk->value, 0, start));
		if (!n_ptr_2)
			exit (1);
		n_ptr_3 = gc(ft_strjoin(n_ptr_2, n_ptr_1));
		if (!n_ptr_3)
			exit (1);
		rm_node(n_ptr_1);
		rm_node(n_ptr_2);
	}
	if (tk->value[end_q + 1])
	{
		n_ptr_2 = gc(ft_substr(tk->value, end_q + 1, \
		(ft_strlen(tk->value) - end_q)));
		if (!n_ptr_2)
			exit (1);
		n_ptr_3 = gc(ft_strjoin(n_ptr_1, n_ptr_2));
		if (!n_ptr_3)
			exit (1);
	}
}
