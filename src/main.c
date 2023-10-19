/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberthod <bberthod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:26:27 by bberthod          #+#    #+#             */
/*   Updated: 2023/10/19 16:17:25 by bberthod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execute.h"

struct						s_state
{
	volatile sig_atomic_t	signal;
}							t_state;

void	interrupt_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		if (t_state.signal)
			;
		else
		{
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
	}
	else if (signum == SIGQUIT)
	{
		if (!t_state.signal)
		{
			rl_on_new_line();
			rl_redisplay();
		}
	}
}

int	is_special_char(char c)
{
	return (c == '|' || c == ' ' || c == '<' || c == '>' || c == '\0');
}

void	tokenise_input(char *input, t_data *data)
{
	int	id;

	id = 0;
	data->temp = ft_calloc(sizeof(t_temp), 1);
	data->temp->tokens = ft_split(input, '|');
	while (data->temp->tokens[id])
		id++;
	data->num_tokens = id;
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_data	*data;

	(void)av;
	if (ac != 1)
		return (ERROR);
	data = ft_calloc(sizeof(t_data), 1);
	data->env = envp;
	t_state.signal = 0;
	signal(SIGINT, interrupt_handler);
	signal(SIGQUIT, interrupt_handler);
	while (1)
	{
		input = ft_readline();
		if (input == NULL)
			printf("exit\n");
		if (input == NULL)
			return (0);
		tokenise_input(input, data);
		parse_token(data);
		//launch_exec_process(data);
		clear_tokens(data);
		free(input);
		t_state.signal = 0;
	}
	free_all(data);
	return (0);
}
