# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/06 22:15:56 by hasmith           #+#    #+#              #
#    Updated: 2019/01/06 22:16:40 by hasmith          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			test_malloc

CC =			clang

FLAGS =			-Wall -Werror -Wextra

FT_MALLOC =		../libft_malloc.so

LIBRARIES =		-L.. -lft_malloc

HEADERS =		-I ../includes -I ../libft

SRC_DIR =		./src/

OBJ_DIR_NAME =	obj
OBJ_DIR =		./obj/

FILENAMES =		main

OBJ_PATHS :=	$(addsuffix .o,$(FILENAMES))
OBJ_PATHS :=	$(addprefix $(OBJ_DIR),$(OBJ_PATHS))

all: $(NAME)

$(NAME): $(FT_MALLOC) $(OBJ_PATHS)
	$(CC) $(FLAGS) $(HEADERS) $(LIBRARIES) $(OBJ_PATHS) -o $(NAME)

$(FT_MALLOC):
	(cd .. && make re)

$(OBJ_PATHS): $(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@/bin/mkdir -p $(OBJ_DIR)
	$(CC) -c $(FLAGS) $(HEADERS) $< -o $@

clean:
	-/bin/rm -f $(OBJ_PATHS)
	/usr/bin/find . -name "$(OBJ_DIR_NAME)" -maxdepth 1 -type d -empty -delete

fclean: clean
	-/bin/rm -f $(NAME)

re: fclean all
	(cd .. && make re)
