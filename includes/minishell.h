/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:42:55 by lefreydier        #+#    #+#             */
/*   Updated: 2023/09/28 12:57:10 by lfreydie         ###   ########.fr       */
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

typedef struct s_tok{
	int				id;
	bool			built_in;
	char			*cmd;
	char			*redir_in;
	char			*redir_out;
	struct s_tok	next;
}					t_tok;

typedef struct s_data{
	char			*tokens[MAX_TOKENS];
	int				num_tokens;
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
