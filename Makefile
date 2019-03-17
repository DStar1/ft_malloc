ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME =			libft_malloc_$(HOSTTYPE).so

LINK =			libft_malloc.so

CC =			clang

FLAGS =			-Wall -Werror -Wextra -fPIC
###############
# NAME = ft_malloc

# FLAGS = -Wall -Wextra -Werror -g

# CC = gcc

SRC_DIR = ./srcs/
OBJ_DIR = ./objs/
INC_DIR = ./includes/
LIBFT_DIR = ./libft/

SRC_FILES = ft_malloc.c ft_free.c
OBJ_FILES = $(SRC_FILES:.c=.o)

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))
LIBFT = $(addprefix $(LIBFT_DIR), libft.a)
LNK  = -L $(LIBFT_DIR)

.SILENT:

all: obj $(LIBFT) $(NAME)

obj:
	@mkdir -p $(OBJ_DIR)
$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	@gcc $(FLAGS) -I $(LIBFT_DIR) -I $(INC_DIR) -o $@ -c $<

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	printf "\033[32m%s\n\033[0m" "Compiling..."
	@$(CC) $(OBJ) $(LNK) -lm $(LIBFT_DIR)/libft.a -shared -o $(NAME)
	printf "\033[32m[ ✔ ] %s\n\033[0m" "Created $(NAME)"
	@/bin/rm -f $(LINK)
	ln -s $(NAME) $(LINK)

clean:
	@rm -Rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	printf "\033[31m[ ✔ ] %s\n\033[0m" "Cleaned $(NAME)"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LINK)
	@make -C $(LIBFT_DIR) fclean
	printf "\033[31m[ ✔ ] %s\n\033[0m" "Fcleaned $(NAME) and $(LINK)"

re: fclean all

t:
	make re
	export DYLD_LIBRARY_PATH=test
	./exec_malloc_test
	export DYLD_LIBRARY_PATH=..

.PHONY: all clean fclean re
