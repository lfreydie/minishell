/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:49:12 by lefreydier        #+#    #+#             */
/*   Updated: 2023/11/08 14:32:51 by lfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_prog(t_data *data)
{
	sig_init();
	data = ft_calloc(sizeof(t_data), 1);
	if (!data)
		exit (1); // code erreur
	init_env(data);
	init_grammar(data);
}

void	init_grammar(t_data *data)
{
	data->grammar = (char **)ft_calloc(6, sizeof (char *));
	if (!data->grammar)
		exit (1); // code erreur
	data->grammar[0] = MUCH_LESS;
	data->grammar[1] = LESS;
	data->grammar[2] = MUCH_MORE;
	data->grammar[3] = MORE;
	data->grammar[4] = BAR;
	data->grammar[5] = S_NEWLINE;
}
