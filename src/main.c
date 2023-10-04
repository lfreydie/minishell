/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blandineberthod <blandineberthod@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:26:27 by bberthod          #+#    #+#             */
/*   Updated: 2023/10/04 15:52:13 by blandineber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_special_char(char c)
{
	return (c == '|' || c == ' ' || c == '<' || c == '>' || c == '\0');
}

void	tokenise_input(char *input, t_data *data)
{
	int	id;

	id = 0;
	data->temp->tokens = ft_split(input, '|');
	while (data->temp->tokens[id])
		id++;
	data->num_tokens = id;
}

int	main(void)
{
	char	*input;
	t_data	*data;

	data = ft_calloc(sizeof(t_data), 1);
	init_data(data);
	while (1)
	{
		input = ft_readline();
		if (!input)
			break ;
		add_history(input);
		tokenise_input(input, data);
		printf("number of tokens : %d\n", data->num_tokens);
		print_tokens1(data);
		parse_token(data);
		print_tokens(data);
		clear_tokens(data);
	}
	free_all(data);
	return (0);
}
