# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alde-abr <alde-abr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/07 15:08:31 by alde-abr          #+#    #+#              #
#    Updated: 2025/07/23 15:45:18 by alde-abr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = \
	main.c func_utils.c parsing.c init_table.c simulation.c \
	mutex_utils.c routine.c time_utils.c philo_utils.c routine_utils.c \
	status.c debug.c

INCLUDES = -Iincludes/

SRC_DIR = src/
OBJ_DIR = obj/

all: $(NAME) $(OBJ_DIR)

#Création des fichiers .o
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

#Création du dossier OBJ_DIR
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

#Compilation des fichiers .c en .o
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

#Création du programme
$(NAME): $(OBJ_DIR) $(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

debug: CFLAGS += -DDEBUG=1
debug: re

.PHONY = all clean fclean re debug
