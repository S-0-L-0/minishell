NAME = minishell
FLAGS = -Wall -Wextra -Werror -g
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
BUILD_DIR = ./src/minishell.c \
            ./src/test/cleanup.c \
            ./src/test/stocazzo.c \
            ./src/test/list_utils.c \
            ./src/test/parser.c \
            ./src/test/pipe_checker.c \
            ./src/test/quote_utils.c \
            ./src/test/tokenizer.c \
            ./src/test/utils.c \
            ./src/test/red_checker.c \
            ./src/executor/create_cmd.c \
            ./src/executor/execute_line.c \
            ./src/executor/find_path.c \
            ./src/executor/redirections.c \
            ./src/utils/ft_split.c \
            ./src/utils/utils.c \

SRC = $(BUILD_DIR)
OBJ = $(SRC:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

%.o: %.c
	gcc $(FLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT)
	gcc $(FLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -o $(NAME) -ltermcap -lreadline

clean:
	rm -f $(OBJ)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re