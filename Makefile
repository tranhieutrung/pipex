# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/07 12:20:30 by hitran            #+#    #+#              #
#    Updated: 2024/07/07 23:58:02 by hitran           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC 				= cc
CFLAGS 			= -Wall -Wextra -Werror
INCLUDES 		= -I./includes -I./mylib/includes

# Directories
MAN_DIR 		= ./mandatory
BONUS_DIR		= ./bonus
MYLIB_DIR	 	= ./mylib

# Source's directories
MAIN_DIR 		= main
ALGO_DIR 		= algo

# Source files by directory
MAIN_FILES 		= 	pipex.c
ALGO_FILES 		= 	controller.c	pathfinder.c	quote.c	spliter.c

MAIN_FILES_BN 	= 	pipex_bonus.c
UTILS_FILES_BN 	= 	

MAN_SRCS		= 	$(addprefix $(MAN_DIR)/$(MAIN_DIR)/, $(MAIN_FILES)) \
					$(addprefix $(MAN_DIR)/$(ALGO_DIR)/, $(ALGO_FILES)) \

BN_SRCS			=	$(addprefix $(BONUS_DIR)/$(MAIN_DIR)/, $(MAIN_FILES_BN)) \
					$(addprefix $(BONUS_DIR)/$(ALGO_DIR)/, $(ALGO_FILES_BN)) \

# Library
MYLIB 			= $(MYLIB_DIR)/mylib.a

# Executables
NAME 			= pipex

# Targets
all: $(NAME)

$(NAME): $(MYLIB) $(MAN_SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) $(MAN_SRCS) $(MYLIB) -o $(NAME)

bonus: .bonus
.bonus: $(MYLIB) $(BN_SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) $(BN_SRCS) $(MYLIB) -o $(NAME)
	@touch .bonus

$(MYLIB):
	$(MAKE) -C $(MYLIB_DIR)

clean:
	$(MAKE) clean -C $(MYLIB_DIR)


fclean: clean
	$(MAKE) fclean -C $(MYLIB_DIR)
	$(RM) $(NAME) $(BONUS) .bonus
	
re: fclean all

.PHONY: all clean fclean re bonus
