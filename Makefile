GREEN	=	\033[1;32m
CYAN	=	\033[0;36m
WHITE	=	\033[0m
CLEAR	=	\r\033[K

NAME = minishell


CC = cc
CFLAGS = -Wall -Wextra -Werror
CFLAGS += -I /opt/homebrew/opt/readline/include
CFLAGS += -I libft
CFLAGS += -I inc

LDFLAGS = -L/opt/homebrew/opt/readline/lib -lreadline

LIBFT = libft/libft.a

SRCS = 	src/main.c						\
		src/init_data.c					\
		src/init_environment.c			\
		src/wait_signal.c				\
		src/modes.c						\
		src/set_prompt.c				\
		src/set_input.c					\
		src/split_input.c				\
		src/split_cmd.c					\
		src/new_token.c					\
		src/expand_content.c			\
		src/execution.c					\
		src/execution_utils1.c			\
		src/execution_utils2.c			\
		src/child_process_utils.c		\
		src/execute_command_utils.c		\
		src/heredoc_proccess.c			\
		src/builtins.c					\
		src/ft_echo.c					\
		src/ft_pwd.c					\
		src/ft_cd.c						\
		src/ft_env.c					\
		src/ft_export.c					\
		src/ft_unset.c					\
		src/ft_exit.c					\
		src/vars_utils1.c				\
		src/vars_utils2.c				\
		src/bools_utils1.c				\
		src/bools_utils2.c				\
		src/write_utils1.c				\
		src/write_utils2.c				\
		src/status_utils.c				\
		src/free_utils1.c				\
		src/free_utils2.c				\


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
