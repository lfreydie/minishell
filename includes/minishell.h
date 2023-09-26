/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blandineberthod <blandineberthod@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:42:55 by lefreydier        #+#    #+#             */
/*   Updated: 2023/09/26 17:01:14 by blandineber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <sys/ioctl.h>
# include <stdlib.h>
# include <termios.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <signal.h>
# include "libft.h"
# include <stdbool.h>


# define MAX_INPUT_LENGTH 1024
# define MAX_TOKENS 100

typedef struct s_tok	t_tok;

typedef struct s_tok{
	char			**cmd; // echo -n "blabalabal"
	// char			**env;
	char			*redir_in; // ce qui va avant <
	char			*redir_out; // ce qui va apres >
	bool			built_in; // true si c'est une des commandes que j'ai ecrit
	t_tok			*next; // si plusieurs commandes c'est la prochaine commande (liste chainee)
}					t_tok;

typedef struct s_data{
	char			*tokens[MAX_TOKENS];
	int				num_tokens;
}					t_data;

//-----------BUILT_IN_COMMANDS----------
void	ft_pwd(void);
void	ft_echo(char **args);
void	ft_cd(char **args);

//----------------UTILS-----------------
char	*ft_strtok(char *str, const char *delimiters);

#endif
