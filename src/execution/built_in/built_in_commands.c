/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blandineberthod <blandineberthod@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:08:59 by bberthod          #+#    #+#             */
/*   Updated: 2023/10/12 14:07:33 by blandineber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

//echo, cd, pwd, export, unset, env, exit

void	ft_pwd(void)
{
	char	buffer[1024];

	if (getcwd(buffer, sizeof(buffer)) != NULL)
		printf("%s\n", buffer);
	else
		perror("getcwd");
}

void	ft_echo(char **args)
{
	if (ft_strncmp(args[0], "echo", ft_strlen(args[0])) == 0)
	{
		if (args[1] == NULL)
		{
			printf("\n");
			return ;
		}
		if (ft_strncmp(args[1], "-n", ft_strlen(args[1])) == 0)
			printf("%s", args[2]);
		else
			printf("%s\n", args[1]);
	}
}

// doesn't work with relative path
void	ft_cd(char **args)
{
	if (ft_strncmp(args[0], "cd", ft_strlen(args[0])) == 0)
	{
		if (args[1] == NULL)
			chdir("/mnt/nfs/homes/bberthod");
		else
		{
			if (chdir(args[1]) != 0)
				perror ("cd");
		}
	}
}

void	ft_export(char **args)
{
	(void)args;
}

void	ft_unset(char **args)
{
	(void)args;
}

int	ft_env(void *ptr)
{
	int		i;
	t_data	*data;

	data = (t_data *)ptr;
	i = 0;
	while (data->env && data->env[i])
		printf("%s\n", data->env[i++]);
	return (0);
}

void	ft_exit(void)
{
	return ;
}
