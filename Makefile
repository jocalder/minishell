GREEN	=	\033[1;32m
CYAN	=	\033[0;36m
WHITE	=	\033[0m
CLEAR	=	\r\033[K

NAME = minishell

CC = gcc -g3 -fsanitize=address
CFLAGS = -Wall -Wextra -Werror
CFLAGS += -I /opt/homebrew/opt/readline/include
CFLAGS += -I libft
CFLAGS += -I inc

LDFLAGS = -L/opt/homebrew/opt/readline/lib -lreadline

LIBFT = libft/libft.a

SRCS = 	src/main.c				\
		src/init_data.c			\
		src/wait_signal.c		\
		src/set_prompt.c		\
		src/set_input.c			\
		src/split_input.c		\
		src/split_cmd.c			\
		src/expand_content.c	\
		src/free_utils.c		\
		src/status_utils.c		\
		src/utils.c				\
		src/delete.c			\
		src/heredoc_proccess.c	\
		src/execution.c			\
		src/execution_utils.c	\
		src/execution_utils2.c	\
		

OBJS = $(SRCS:%.c=objs/%.o)

all: $(LIBFT) $(NAME)

$(NAME): objs $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(LDFLAGS)
	@echo "$(GREEN)minishell ready$(WHITE)"

$(LIBFT):
	@make --silent -C libft

objs:
	@mkdir -p objs/src/

objs/%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make --silent clean -C libft
	@rm -rf objs
	@echo "Objetcs files deleted."

fclean: clean
	@make --silent fclean -C libft
	@rm -f $(NAME)
	@echo "Full clean completed"

re: fclean all

.PHONY: all clean fclean re
