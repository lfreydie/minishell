# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/07 15:01:41 by lfreydie          #+#    #+#              #
#    Updated: 2023/12/20 23:48:46 by lfreydie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC ?= gcc
NAME := minishell
CFLAGS += -Wall -Wextra -Werror -g3
LIB_FLAGS = -L$(LIBFT_DIR) -lft -lreadline


HD_DIR = ./includes
SRC_DIR = ./src
OBJ_DIR = ./objs
LIBFT_DIR = ./libft


RM = rm -f
RM_OPT = -r

INIT_PROC = init/init_process
BUILT = execution/built_in/built_in_cmd

LIBFT = $(LIBFT_DIR)/libft.a

GREEN=\033[0;32m
BLUE=\033[0;34m
RED=\033[0;31m
PINK=\033[0;35m
END=\033[0m

SRC_F =	main.c sig.c read_line.c \
		init/init_programme/init_env.c init/init_programme/init_prog.c \
		$(INIT_PROC)/token.c $(INIT_PROC)/syntax.c $(INIT_PROC)/parse.c $(INIT_PROC)/init_utils.c $(INIT_PROC)/init_process.c \
		$(INIT_PROC)/redirection/redir.c $(INIT_PROC)/redirection/heredoc.c \
		$(INIT_PROC)/expand/expand.c $(INIT_PROC)/expand/expand_var_utils.c $(INIT_PROC)/expand/expand_utils.c $(INIT_PROC)/expand/expand_string_utils.c \
		exit/error.c exit/garbage_collector.c exit/garbage_collector_utils.c \
		execution/pipex.c execution/exec_utils.c execution/exec.c \
		$(BUILT)/built_cd.c $(BUILT)/built_echo.c $(BUILT)/built_env.c $(BUILT)/built_exit.c $(BUILT)/built_export_utils.c \
		$(BUILT)/built_export.c $(BUILT)/built_pwd.c $(BUILT)/built_unset.c $(BUILT)/built_utils.c $(BUILT)/env_modif.c \
		execution/built_in/built_in_process.c
SRC = $(addprefix $(SRC_DIR)/, $(SRC_F))
OBJ = $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SRC:.c=.o))

$(NAME) :	$(LIBFT) $(OBJ)
	@echo "$(BLUE) ==== Project compiling ==== $(END)"
	@$(CC) $(CFLAGS) -I $(HD_DIR) $(OBJ) $(LIB_FLAGS) $(LIBFT) -o $(NAME)
	@echo "$(GREEN) ==== Project compiled ==== $(END)"

$(LIBFT) :
	@echo "$(BLUE) ==== libft compiling ==== $(END)"
	@make -s -C $(LIBFT_DIR)
	@echo "$(GREEN) ==== libft compiled ==== $(END)"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(HD_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I $(HD_DIR) -c $< -o $@

all :	$(NAME)

clean :
	@$(RM) $(RM_OPT) $(OBJ_DIR)
	@make clean -sC $(LIBFT_DIR)
	@echo "$(PINK) ==== All object removed ==== $(END)"

fclean :	clean
	@$(RM) $(NAME)
	@make fclean -sC $(LIBFT_DIR)
	@echo "$(RED) ==== Executables removed ==== $(END)"

scan :
	@echo "	$(BLUE) ==== Scan running ==== $(END)"
	@scan-build-12 make -s
	@echo "	$(GREEN) ==== Scan finished ==== $(END)"

re :	fclean all

.PHONY : all clean fclean scan re
