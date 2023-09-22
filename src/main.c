/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberthod <bberthod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:26:27 by bberthod          #+#    #+#             */
/*   Updated: 2023/09/22 18:19:21 by bberthod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_tokens(t_data *data)
{
	int	i;

	i = 0;
	while (data->tokens[i] != NULL)
	{
		printf("Token %d : %s\n", i, data->tokens[i]);
		i++;
	}
}

int	is_special_char(char c)
{
	return (c == '|' || c == ' ' || c == '<' || c == '>' || c == '\0');
}

void	tokenise_input(char *input, t_data *data)
{
	char	*token;
	char	special_char[2];
	int		len;

	data->num_tokens = 0;
	token = ft_strtok(input, " \t\n");
	while (token != NULL && data->num_tokens < MAX_TOKENS)
	{
		len = ft_strlen(token);
		if (len > 1 && is_special_char(token[len - 1]))
		{
			special_char[0] = token[len - 1];
			special_char[1] = '\0';
			token[len - 1] = '\0';
			data->tokens[data->num_tokens++] = ft_strdup(token);
			data->tokens[data->num_tokens++] = ft_strdup(special_char);
		}
		else
			data->tokens[data->num_tokens++] = ft_strdup(token);
		token = ft_strtok(NULL, " \t\n");
	}
	data->tokens[data->num_tokens] = NULL;
}

int	main(void)
{
	char	input[MAX_INPUT_LENGTH];
	t_data	data;
	int		i;
	char	c;


	while (1)
	{
		write(STDOUT_FILENO, "myShell> ", 10);
		i = 0;
		while (read(STDIN_FILENO, &c, 1) && c != '\n'
			&& i < MAX_INPUT_LENGTH - 1)
			input[i++] = c;
		input[i] = '\0';
		tokenise_input(input, &data);
		printf("number of tokens : %d\n", data.num_tokens);
		print_tokens(&data);
	}
	return (0);
}
