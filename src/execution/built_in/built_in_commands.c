/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefreydier <lefreydier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:08:59 by bberthod          #+#    #+#             */
/*   Updated: 2023/12/07 17:15:37 by lefreydier       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

//echo, cd, pwd, export, unset, env, exit

void	ft_pwd(void)
{
	char	path;

	path = gc(getcwd(NULL, 0));
	if (path)
		printf("%s\n", path);
	else
		return (perror("getcwd"), NULL);
}

void	ft_echo(char **args)
{
	int	i;
	int	flag;

	if (ft_strncmp(args[0], "echo", ft_strlen(args[0])) == 0)
	{
		if (args[1] == NULL)
		{
			printf("\n");
			return ;
		}
		i = 1;
		flag = ft_memcmp(args[i], "-n", ft_strlen(args[i]));
		if (!flag)
			i++;
		while (args[i])
		{
			printf("%s", args[i]);
			if (args[i + 1])
				printf(" ");
			else if (flag)
				printf("\n");
			i++;
		}
	}
}

// doesn't work with relative path
void	ft_cd(t_data *data, t_cmd *cmd)
{
	char	*dir;

	if (cmd->n_args_cmd > 2)
		return (printf("erreur nb args"), 1);
	dir = getenv("PWD");
	ft_export("OLDPWD", dir, data);
	if (cmd->n_args_cmd == 1 && chdir(getenv("HOME")) == -1)
		return (printf("Home not set"), 1);
	if (cmd->n_args_cmd > 1 && chdir(cmd->value[1]) == -1)
		return (printf("Erreur"), 1);
	dir = gc(getcwd(NULL, 0));
	ft_export("PWD", dir, data);
}

void	ft_export(char *name, char *value, t_data *data)
{

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
