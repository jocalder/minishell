# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/18 22:28:58 by vgoyzuet          #+#    #+#              #
#    Updated: 2025/06/27 05:51:44 by vgoyzuet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN	=	\033[1;32m
CYAN	=	\033[0;36m
WHITE	=	\033[0m
CLEAR	=	\r\033[K

NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -fPIC

SRCS	=	ft_isalpha.c			\
			ft_isdigit.c			\
			ft_isalnum.c			\
			ft_isascii.c			\
			ft_isprint.c			\
			ft_toupper.c			\
			ft_tolower.c			\
			ft_strlen.c				\
			ft_strchr.c				\
			ft_strrchr.c			\
			ft_strncmp.c			\
			ft_memset.c				\
			ft_bzero.c				\
			ft_memcpy.c				\
			ft_memmove.c			\
			ft_memchr.c				\
			ft_memcmp.c				\
			ft_strlcpy.c			\
			ft_strcpy.c				\
			ft_strlcat.c			\
			ft_strnstr.c			\
			ft_atoi.c				\
			ft_atol.c				\
			ft_calloc.c				\
			ft_realloc.c			\
			ft_strdup.c				\
			ft_substr.c				\
			ft_strjoin.c			\
			ft_strtrim.c			\
			ft_split.c				\
			ft_itoa.c				\
			ft_strmapi.c			\
			ft_striteri.c			\
			ft_putchar_fd.c			\
			ft_putstr_fd.c			\
			ft_putendl_fd.c			\
			ft_putnbr_fd.c			\
			ft_lstnew_bonus.c		\
			ft_lstadd_front_bonus.c	\
			ft_lstsize_bonus.c		\
			ft_lstlast_bonus.c		\
			ft_lstadd_back_bonus.c	\
			ft_lstdelone_bonus.c	\
			ft_lstclear_bonus.c		\
			ft_lstiter_bonus.c		\
			ft_lstmap_bonus.c		\
			ft_printf.c				\
			ft_perror.c				\
			ft_printf_utils.c		\
			ft_print_stack.c		\
			get_next_line.c			\
			ft_free_array.c			\
			ft_abs.c				\
	
OBJS = $(SRCS:%.c=objs/%.o)

all: $(NAME)

$(NAME): objs $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@echo "$(CLEAR)$(CYAN)libft.a successfully created."

objs:
	@mkdir -p objs

objs/%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "$(CLEAR)$(CYAN)Compiling $<..."

clean:
	@rm -rf objs
	@echo "Libft -> Objetcs files deleted."

fclean: clean
	@rm -f $(NAME)
	@echo "Clean completed, libft.a deleted."

re: fclean all

.PHONY: all clean fclean re
