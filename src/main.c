/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blandineberthod <blandineberthod@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:26:27 by bberthod          #+#    #+#             */
/*   Updated: 2023/10/12 15:14:23 by blandineber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execute.h"

volatile sig_atomic_t g_running = true;
volatile sig_atomic_t g_print_newline = false;

void	handle_sigint(int sig)
{
	(void) sig;
	printf("\n%s", get_prompt());
	fflush(stdout);
	g_print_newline = true;
}

void	handle_sigquit(int sig)
{
	(void) sig;
	printf("\b\b \b\b");
	g_print_newline = false;
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
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	while (g_running)
	{
		input = ft_readline();
		if (g_print_newline)
		{
			printf("\n");
			g_print_newline = false;
		}
		if (!input)
		{
			printf("exit\n");
			data->exit_flag = 1;
			g_running = false;
			break ;
		}
		tokenise_input(input, data);
		parse_token(data);
		//launch_exec_process(data);
		clear_tokens(data);
		free(input);
	}
	free_all(data);
	return (0);
}
