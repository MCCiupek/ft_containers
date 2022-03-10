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

# OBJS			=		$(SRCS:.cpp=.o)
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


all: echoCL_ft ft echoCS echoCL_std std echoCS

$(OBJS_FT): $(OBJDIR_FT)%.o : $(SRCS)
	$(CC) $(FLAGS) -D TESTED_NAMESPACE_FT -I $(DIR_HEADERS) -c $< -o $@

$(OBJS_STD): $(OBJDIR_STD)%.o : $(SRCS)
	$(CC) $(FLAGS) -D TESTED_NAMESPACE_STD -I $(DIR_HEADERS) -c $< -o $@

ft: $(OBJS_FT)
	$(CC) $(FLAGS) -D TESTED_NAMESPACE_FT $< -o $(NAME_FT)
	printf "$(GREEN)██"

std: $(OBJS_STD)
	$(CC) $(FLAGS) -D TESTED_NAMESPACE_STD $< -o $(NAME_STD)
	printf "$(GREEN)██"

clean: echoCLEAN
	$(RM) $(OBJS_FT) $(OBJS_STD)

fclean: clean
	$(RM) $(NAME) $(NAME_FT) $(NAME_STD)

git: fclean
	git pull
	git add .
	git commit -m "$(shell date)"
	git push

re: fclean all

.PHONY: all, clean, fclean, re, git, bonus, ft, std

.SILENT:

### COLOR ###

RESET = \033[0m
BLACK = \033[0;30m
RED = \033[0;31m
GREEN = \033[32m
YELLOW = \033[33;33m
BLUE = \033[0;34m
PURPLE = \033[1;35m
CYAN = \033[1;36m
WHITE = \033[0;37m

### ECHO ###

echoCL:
	printf "\n$(YELLOW)===> Compiling $(RED)$(NAME)$(RESET)\n"

echoCL_ft:
	printf "\n$(YELLOW)===> Compiling $(RED)$(NAME_FT)$(RESET)\n"

echoCL_std:
	printf "\n$(YELLOW)===> Compiling $(RED)$(NAME_STD)$(RESET)\n"

echoCS :
	printf "$(GREEN)OK\n"

echoCLEAN :
	printf "$(PURPLE)$(NAME) ===> Cleaning$(RESET)\n"
