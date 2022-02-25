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

OBJS			=		$(SRCS:.cpp=.o)

NAME			=		test

UNAME			:=		$(shell uname)

ifeq ($(UNAME),Darwin)
	OS = -D MACOS
endif

ifeq ($(UNAME),Linux)
	OS = -D LINUX
endif

all:			$(NAME)

$(NAME) :		echoCL $(OBJS) $(HEADERS) echoCS 
				$(CC) $(FLAGS) $(OS) $(OBJS) -o $(NAME)

san:			echoCLsan $(OBJS) $(HEADERS) echoCS
				$(CC) $(FLAGS) $(FSANITIZE) $(OS) $(OBJS) -o $(NAME)

%.o: %.cpp
				$(CC) $(FLAGS) $(OS) -I $(DIR_HEADERS) -c $< -o $@
				printf "$(GREEN)██"

clean:			echoCLEAN
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

git:			fclean
				git pull
				git add .
				git commit -m "$(shell date)"
				git push

re:				fclean all

.PHONY:			all, clean, fclean, re, git, bonus, san

.SILENT:

# COLOR
#----------------reset----------------#
NC = \033[0m

#-----------Regular Colors------------#
BLACK = \033[0;30m
RED = \033[0;31m
GREEN = \033[32m
YELLOW = \033[33;33m
BLUE = \033[0;34m
PURPLE = \033[1;35m
CYAN = \033[1;36m
WHITE = \033[0;37m

###########################ECHO
echoCL:
	printf "\n$(YELLOW)===> Compiling $(RED)$(NAME)$(NC)\n"

echoCLsan:
	printf "\n$(YELLOW)===> Compiling with fsanitize $(RED)$(NAME)$(NC)\n"

echoCS :
	printf "$(GREEN)OK\n"

echoCLEAN :
	printf "$(PURPLE)$(NAME) ===> Cleaning$(NC)\n"

echoFCLEAN :
	printf "$(PURPLE)$(NAME) ===> Cleaning Exec & Lib$(NC)\n"