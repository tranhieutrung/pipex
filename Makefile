# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/07 12:20:30 by hitran            #+#    #+#              #
#    Updated: 2024/07/31 23:46:58 by hitran           ###   ########.fr        #
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
MAN_FILES 		= 	execute_pipex.c 				handle_errors.c	\
					find_command_path.c				spit_command.c	
					
BONUS_FILES 	= 	execute_pipex_bonus.c 			handle_errors_bonus.c	\
					find_command_path_bonus.c		spit_command_bonus.c	\
					read_here_doc_bonus.c

MAN_SRCS		= 	main.c	$(addprefix $(MAN_DIR)/, $(MAN_FILES))

BONUS_SRCS		=	main_bonus.c $(addprefix $(BONUS_DIR)/, $(BONUS_FILES))
					
# Library
MYLIB 			= $(MYLIB_DIR)/mylib.a

# Executables
NAME 			= pipex

# Targets
all : mandatory

mandatory : .mandatory
.mandatory: $(MYLIB) $(MAN_SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) $(MAN_SRCS) $(MYLIB) -o $(NAME)
	@touch .mandatory
	@rm -f .bonus

bonus: .bonus
.bonus: $(MYLIB) $(BONUS_SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) $(BONUS_SRCS) $(MYLIB) -o $(NAME)
	@touch .bonus
	@rm -f .mandatory
	
$(MYLIB):
	$(MAKE) -C $(MYLIB_DIR)

clean:
	$(MAKE) clean -C $(MYLIB_DIR)


fclean: clean
	$(MAKE) fclean -C $(MYLIB_DIR)
	$(RM) $(NAME) .bonus .mandatory
	
re: fclean all

.PHONY: all clean fclean re mandatory bonus