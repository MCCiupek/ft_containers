# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mciupek <mciupek@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/03 19:40:40 by mciupek           #+#    #+#              #
#    Updated: 2022/01/26 00:26:38 by mciupek          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				=		clang++

FLAGS			=		-Wall -Wextra -Werror -std=c++98
FSANITIZE		=		-fsanitize=address -g3

RM				=		rm -rf

DIR_HEADERS		=		./includes/

HEADER			=		algorithm.hpp	\
						iterator.hpp	\
						map.hpp			\
						type_traits.hpp	\
						utility.hpp		\
						vector.hpp

HEADERS			=		$(addprefix $(DIR_HEADERS), $(HEADER))

DIR_SRCS		=		./srcs/

SRC				=		main.cpp

SRCS			=		$(addprefix $(DIR_SRCS), $(SRC))

OBJS			=		main.o

OBJDIR_FT		=		./obj/ft/

OBJDIR_STD		=		./obj/std/

OBJS_FT			=		$(addprefix $(OBJDIR_FT),$(OBJS))

OBJS_STD 		=		$(addprefix $(OBJDIR_STD),$(OBJS))

NAME			=		containers

NAME_FT			=		test_ft

NAME_STD		=		test_std

UNAME			:=		$(shell uname)

ifeq ($(UNAME),Darwin)
	OS = -D MACOS
endif

ifeq ($(UNAME),Linux)
	OS = -D LINUX
endif


all: ft std

$(OBJS_FT): $(OBJDIR_FT)%.o : $(SRCS)
	$(CC) $(FLAGS) -D TESTED_NAMESPACE_FT -I $(DIR_HEADERS) -c $< -o $@

$(OBJS_STD): $(OBJDIR_STD)%.o : $(SRCS)
	$(CC) $(FLAGS) -D TESTED_NAMESPACE_STD -I $(DIR_HEADERS) -c $< -o $@

ft: $(OBJS_FT)
	$(CC) $(FLAGS) -D TESTED_NAMESPACE_FT $< -o $(NAME_FT)

std: $(OBJS_STD)
	$(CC) $(FLAGS) -D TESTED_NAMESPACE_STD $< -o $(NAME_STD)

clean:
	$(RM) $(OBJDIR_FT)*.o $(OBJDIR_STD)*.o

fclean: clean
	$(RM) $(NAME) $(NAME_FT) $(NAME_STD)
	$(RM) ft_out std_out diff

git: fclean
	git pull
	git add .
	git commit -m "$(shell date)"
	git push

re: fclean all

test: all
	./$(NAME_FT) 42 > ft_out
	./$(NAME_STD) 42 > std_out

.PHONY: all, clean, fclean, re, git, bonus, ft, std, test, diff, ft_out, std_out

.SILENT: