/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefreydier <lefreydier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:06:10 by blandineber       #+#    #+#             */
/*   Updated: 2023/10/05 19:05:48 by lefreydier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parse_cmd(char **tab, t_tok *new_token, int id)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tab[i])
	{
		if (ft_strncmp(tab[i], "<", ft_strlen(tab[i]))
			&& ft_strncmp(tab[i], ">", ft_strlen(tab[i])))
		{
			if (i > 0 && ft_strncmp(tab[i - 1], "<", ft_strlen(tab[i - 1]))
				&& ft_strncmp(tab[i - 1], ">", ft_strlen(tab[i - 1])))
			{
				new_token->cmd[j] = tab[i];
				j++;
			}
		}
		i++;
	}
}

void	parse_redir_in(char **tab, t_tok *new_token, int id)
{
	int		i;
	int		fd;

	i = 0;
	while (tab[i])
	{
		if (ft_strncmp(tab[i], "<", ft_strlen(tab[i])) == 0)
		{
			if (new_token->redir_in != NULL)
			{
				fd = open(new_token->redir_in);
				if (fd < 0)
					perror("open");
				close(fd);
			}
			if (ft_strncmp(tab[i], "<<", ft_strlen(tab[i])) == 0)
				heredoc_set(new_token, tab[i + 1]);
			else
				new_token->redir_in = tab[i + 1];
		}
		i++;
	}
}

void	parse_redir_out(char **tab, t_tok *new_token, int id)
{
	int		i;
	int		fd;

	i = 0;
	while (tab[i])
	{
		if (ft_strncmp(tab[i], ">", ft_strlen(tab[i])) == 0)
		{
			if (new_token->redir_out != NULL)
			{
				fd = open(new_token->redir_out);
				if (fd < 0)
					perror("open");
				close(fd);
			}
			if (ft_strncmp(tab[i], ">>", ft_strlen(tab[i])) == 0)
				new_token->append = true;
			new_token->redir_out = tab[i + 1];
		}
		i++;
	}

}

void	parse_token(t_data *data)
{
	int		id;
	t_tok	*new_token;

	id = 0;
	while (data->temp->tokens[id])
	{
		new_token = create_token();
		new_token->id = id;
		data->temp->tab_cmd = ft_split(data->temp->tokens[id], ' ');
		parse_redir_in(data->temp->tab_cmd, new_token, id);
		parse_redir_out(data->temp->tab_cmd, new_token, id);
		parse_cmd(data->temp->tab_cmd, new_token, id);
		add_token(data, new_token);
		id++;
	}
}
