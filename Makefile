# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmafueni <jmafueni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/18 22:15:44 by jmafueni          #+#    #+#              #
#    Updated: 2025/01/24 00:48:18 by jmafueni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_DIR = src
OBJ_DIR = obj
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC = $(SRC_DIR)/main.c \
	  $(SRC_DIR)/exec/builtins_utils.c \
	  $(SRC_DIR)/exec/builtins.c \
	  $(SRC_DIR)/exec/change_dir.c \
	  $(SRC_DIR)/exec/exec_exit.c \
	  $(SRC_DIR)/exec/export.c \
	  $(SRC_DIR)/exec/fd_utils.c \
	  $(SRC_DIR)/exec/files_check.c \
	  $(SRC_DIR)/exec/get_command.c \
	  $(SRC_DIR)/exec/hdoc.c \
	  $(SRC_DIR)/exec/pipex.c \
	  $(SRC_DIR)/exec/utils_exec.c \
	  $(SRC_DIR)/expand/env_create.c \
	  $(SRC_DIR)/expand/env_utils.c \
	  $(SRC_DIR)/expand/env.c \
	  $(SRC_DIR)/expand/expand_check_utils.c \
	  $(SRC_DIR)/expand/expand_check.c \
	  $(SRC_DIR)/expand/split_expand.c \
	  $(SRC_DIR)/expand/split_expand_utils.c \
	  $(SRC_DIR)/lib_token/cmd_utils.c \
	  $(SRC_DIR)/lib_token/create_cmd.c \
	  $(SRC_DIR)/lib_token/do_cmd.c \
	  $(SRC_DIR)/lib_token/ft_clear.c \
	  $(SRC_DIR)/lib_token/mini_libft.c \
	  $(SRC_DIR)/lib_token/redir_utils.c \
	  $(SRC_DIR)/lib_token/token.c \
      $(SRC_DIR)/lib_token/type_token.c \
	  $(SRC_DIR)/lib_token/utils.c \
	  $(SRC_DIR)/lib_token/utils_var.c \
	  $(SRC_DIR)/lib_token/utils_quotes.c \
	  $(SRC_DIR)/parsing/analyse_synthax.c \
	  $(SRC_DIR)/parsing/check_quotes.c \
	  $(SRC_DIR)/parsing/parse_utils.c \
	  $(SRC_DIR)/parsing/signal_utils.c \
	  $(SRC_DIR)/parsing/signal.c 

OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

CC = gcc
FLAGS = -Wall -Wextra -Werror -g3 -I$(LIBFT_DIR) -I/usr/include

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(OBJ) $(LIBFT) -o $@ $(FLAGS) -lreadline

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@) # Crée les sous-dossiers nécessaires
	$(CC) $(FLAGS) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ_DIR)
	make clean -C $(LIBFT_DIR)
	echo "\033[1;31m======== object files removed ========\033[0m"

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)
	echo "\033[1;31m======= executable removed =======\033[0m"

re: fclean all

.PHONY: all clean fclean re

