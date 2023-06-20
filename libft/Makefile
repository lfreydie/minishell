# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfreydie <lfreydie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/17 10:31:53 by lefreydier        #+#    #+#              #
#    Updated: 2023/01/28 12:50:06 by lfreydie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC	=	cc

CFLAGS	=	-Wall -Wextra -Werror

NAME	=	libft.a

RM	=	rm -f

AR	=	ar -rcs

HDIR	=	./includes/

SDIR	=	./src/

INCLUDE	=	$(HDIR)libft.h

# Colors
GREEN=\033[0;32m
RED=\033[0;31m
PINK=\033[0;35m
BLUE=\033[0;34m
END=\033[0m

#main
SOURCES	+=	$(SDIR)ft_atoi.c $(SDIR)ft_bzero.c $(SDIR)ft_isalnum.c $(SDIR)ft_isalpha.c $(SDIR)ft_tolower.c \
			$(SDIR)ft_isascii.c $(SDIR)ft_isdigit.c $(SDIR)ft_isprint.c $(SDIR)ft_memchr.c $(SDIR)ft_memcpy.c \
			$(SDIR)ft_memcmp.c $(SDIR)ft_memset.c $(SDIR)ft_strchr.c $(SDIR)ft_strlcat.c $(SDIR)ft_toupper.c \
			$(SDIR)ft_strlcpy.c $(SDIR)ft_strlen.c $(SDIR)ft_strncmp.c $(SDIR)ft_calloc.c $(SDIR)ft_strrchr.c \
			$(SDIR)ft_memmove.c $(SDIR)ft_strdup.c $(SDIR)ft_strnstr.c $(SDIR)ft_strjoin.c $(SDIR)ft_putchar_fd.c \
			$(SDIR)ft_putstr_fd.c $(SDIR)ft_putendl_fd.c $(SDIR)ft_putnbr_fd.c $(SDIR)ft_strmapi.c \
			$(SDIR)ft_strtrim.c $(SDIR)ft_substr.c $(SDIR)ft_split.c $(SDIR)ft_itoa.c $(SDIR)ft_striteri.c

#main 2
SOURCES	+=	$(SDIR)ft_lstnew.c $(SDIR)ft_lstadd_front.c $(SDIR)ft_lstsize.c $(SDIR)ft_lstlast.c \
			$(SDIR)ft_lstadd_back.c $(SDIR)ft_lstdelone.c $(SDIR)ft_lstclear.c \
			$(SDIR)ft_lstiter.c $(SDIR)ft_lstmap.c
#ft_printf
SOURCES	+=	$(SDIR)ft_i_utoa.c $(SDIR)ft_print_ptr.c $(SDIR)ft_printf.c $(SDIR)ft_put_hex.c\
			$(SDIR)ft_putchar.c $(SDIR)ft_putnbr_u.c $(SDIR)ft_putstr.c $(SDIR)ft_strchr.c\
			$(SDIR)ft_strlen.c

#get_next_line
SOURCES	+=	$(SDIR)get_next_line.c $(SDIR)get_next_line_utils.c

OBJECTS	=	$(SOURCES:.c=.o)

%.o : %.c
		@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJECTS) $(INCLUDE)
			@$(AR) $(NAME) $(OBJECTS)
			@echo "$(GREEN) ==== libft compiled ==== $(END)"

all:	$(NAME)

clean:
		@$(RM) $(OBJECTS)
		@echo "$(BLUE) ==== All objects removed ==== $(END)"

fclean:	clean
		@$(RM) $(NAME)
		@echo "$(PINK) ==== All executables removed ==== $(END)"

re:	fclean all

.PHONY:	all clean fclean re
