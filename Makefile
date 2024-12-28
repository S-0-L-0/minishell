NAME = minishell
FLAGS = -Wall -Wextra -Werror -g
LIBFT_DIR =	./libft
LIBFT = $(LIBFT_DIR)/libft.a
BUILD_DIR = ./src/test/main.c \
			./src/test/cleanup.c \
			./src/test/list_utils.c \
			./src/test/parser.c\
			./src/test/pipe_checker.c \
			./src/test/quote_utils.c \
			./src/test/tokenizer.c \
			./src/test/utils.c \
			./src/executor/create_cmd.c \
			./src/executor/execute_line.c \
			./src/executor/find_path.c \
			./src/utils/ft_split.c \
			./src/utils/libft_func.c \
			./src/utils/utils.c \
			./src/executor/redirections.c \

SRC = $(BUILD_DIR) ## file.c 
OBJ = $(SRC:%.c=%.o)

all: $(NAME)
$(NAME):	$(OBJ)
		@make -C libft
		gcc $(OBJ) ${LIBFT} -o $(NAME) -ltermcap

clean:
	  rm -f $(OBJ)
	  @make clean -C libft
	  

fclean:	clean
	   rm -f $(NAME)
	   @make fclean -C libft

re: fclean all 