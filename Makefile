# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/07 12:20:30 by hitran            #+#    #+#              #
#    Updated: 2024/07/12 21:29:16 by hitran           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC 				= cc
CFLAGS 			= -Wall -Wextra -Werror
INCLUDES 		= -I./includes -I./mylib/includes

# Directories
MAN_DIR 		= ./srcs/mandatory
BONUS_DIR		= ./srcs/bonus
MYLIB_DIR	 	= ./mylib

# Source files by directory
MAN_FILES 		= 	main.c					execute_pipex.c 	\
					find_command_path.c		spit_command.c

BONUS_FILES 	= 	main_bonus.c
	

MAN_SRCS		= 	$(addprefix $(MAN_DIR)/, $(MAN_FILES))

BONUS_SRCS		=	$(addprefix $(BONUS_DIR)/, $(BONUS_FILES))
					
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