# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: miparis <miparis@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/20 12:32:22 by miparis           #+#    #+#              #
#    Updated: 2025/03/06 16:37:48 by miparis          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS =  src/main.c \
		src/args.c \
		src/utils.c \
		src/wrappers.c \
		src/inits.c \
		src/simulation.c \
		src/syncronization.c \
		src/get_set.c

# Define Colors
GREEN  := \033[1;32m  # Bold Green
YELLOW := \033[0;33m  # Non-bold Yellow
RED    := \033[0;31m  # Regular Red
BLUE   := \033[1;34m  # Bold Blue
PURPLE := \033[1;35m  # Bold Purple
BOLD   := \033[1m     # Bold Text
NC     := \033[0m     # No Color (Resets color and style)

OBJS = ${SRCS:.c=.o}

.SILENT: $(OBJS)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3
REMOVE = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(BOLD)$(BLUE)Philosophers are now operative$(NC)"

clean:
	@$(REMOVE) $(NAME)
	@$(REMOVE) $(OBJS)

fclean: clean
	@$(REMOVE) $(NAME)
	@echo "$(BOLD)$(GREEN)🧹Everything cleaned up!$(NC)"

re: fclean all

clear:
	@clear

.PHONY: all clean fclean re clear bonus
