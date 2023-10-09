/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blandineberthod <blandineberthod@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:26:27 by bberthod          #+#    #+#             */
/*   Updated: 2023/10/09 16:58:42 by blandineber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execute.h"

void	handle_sigint(int sig)
{
	(void) sig;
	printf("\n");
	printf("%s", get_prompt());
}

void	handle_sigquit(int sig)
{
	(void) sig;
	return ;
}


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

	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	data = ft_calloc(sizeof(t_data), 1);
	init_data(data);
	while (1)
	{
		input = ft_readline();
		if (!input)
		{
			printf("exit\n");
			data->exit_flag = 1;
			break ;
		}
		// add_history(input);
		tokenise_input(input, data);
		parse_token(data);
		launch_exec_process(data);
		clear_tokens(data);
	}
	free_all(data);
	return (0);
}
