# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dochoi <dochoi@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/21 00:08:29 by dochoi            #+#    #+#              #
#    Updated: 2020/07/21 15:55:23 by dochoi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
FLAGS = -Wall -Wextra -Werror
SRC_NAME = ./save_bitmap.c ./key_event.c ./show_bonus.c \
			./show_c_f.c ./display_error.c ./list_sort.c ./show_life.c \
			./main.c ./show_sprite.c ./dochoi_show.c ./map_check.c ./show_wall.c \
			./flag_parse.c ./map_parse.c ./sp_list_utils.c ./flag_parse2.c \
			./map_parse2.c ./v_check.c ./v_check2.c \
			./h_check.c		./player_set.c
LIB_SRC_NAME = ./ft_memset.c ./ft_bzero.c ./ft_memcpy.c ./ft_memccpy.c \
		./ft_memmove.c ./ft_memchr.c ./ft_memcmp.c ./ft_strlen.c \
		./ft_strlcpy.c ./ft_strlcat.c ./ft_strchr.c ./ft_strrchr.c \
		./ft_strnstr.c ./ft_strncmp.c ./ft_atoi.c ./ft_isalpha.c \
		./ft_isdigit.c ./ft_isalnum.c ./ft_isascii.c ./ft_isprint.c \
		./ft_tolower.c ./ft_toupper.c ./ft_calloc.c ./ft_strdup.c \
		./ft_substr.c ./ft_strjoin.c ./ft_strtrim.c ./ft_split.c \
		./ft_itoa.c ./ft_strmapi.c ./ft_putchar_fd.c ./ft_putstr_fd.c \
		./ft_putendl_fd.c ./ft_putnbr_fd.c \
		./ft_lstadd_back.c ./ft_lstadd_front.c ./ft_lstclear.c ./ft_lstdelone.c\
		./ft_lstiter.c ./ft_lstlast.c ./ft_lstmap.c ./ft_lstnew.c ./ft_lstsize.c
GNL_SRC_NAME = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

OBJ_NAME = $(SRC_NAME:.c=.o)
LIB_OBJ_NAME = $(LIB_SRC_NAME:.c=.o)
OBJ_PATH = ./obj
OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_NAME))
LIB_OBJ = $(addprefix $(OBJ_PATH)/, $(LIB_OBJ_NAME))
INC_LINK = -I./includes

$(OBJ_PATH)/%.o: %.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	gcc $(FLAGS) $(INC_LINK) -o $@ -c $<

$(NAME) : $(OBJ) libft.a
	gcc $(SRC_NAME) $(GNL_SRC_NAME) -lmlx -framework OpenGL -framework AppKit ./libft/libft.a -o $@
	@echo "complete\n"

all : $(NAME)

libft.a :
	@$(MAKE) -C ./libft fclean
	@$(MAKE) -C ./libft bonus
	@for i in $(LIB_OBJ_NAME); do cp ./libft/$$i ./$(OBJ_PATH); done
	cp ./libft/$@ ./
	@echo "moved lib's objfile\n"

bonus : all

clean :
	@$(MAKE) -C ./libft clean
	@rm -rf ./obj libft.a

fclean : clean
	@$(MAKE) -C ./libft fclean
	@rm -rf ./obj $(NAME) libft.a

re : fclean all
.PHONY: all fclean bonus re
