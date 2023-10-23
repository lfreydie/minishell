/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefreydier <lefreydier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:10:11 by lefreydier        #+#    #+#             */
/*   Updated: 2023/10/20 18:32:03 by lefreydier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_process(t_data *data, char *input)
{
	data->line = input;
	init_grammar(data);
	tokenize_input(data);
	print_token(data);
	// parse_token(data);
}

void	init_grammar(t_data *data)
{
	data->grammar = (char **)ft_calloc(6, sizeof (char *));
	if (!data->grammar)
		exit (1); // code erreur
	data->grammar[0] = LESS;
	data->grammar[1] = MUCH_LESS;
	data->grammar[2] = MORE;
	data->grammar[3] = MUCH_MORE;
	data->grammar[4] = BAR;
	data->grammar[5] = S_NEWLINE;
}
