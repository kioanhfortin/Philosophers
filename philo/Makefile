# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kfortin <kfortin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/25 11:04:35 by kfortin           #+#    #+#              #
#    Updated: 2024/02/18 13:50:17 by kfortin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

###############################################################################
#							    PROGRAM NAMES	      					  	  #
###############################################################################

NAME		=	philo
HEADER_F	=	philo.h

###############################################################################
#							    SYSTEM VARIABLES       					  	  #
###############################################################################

# CFLAGS			=	-Wall -Werror -Wextra -fsanitize=thread -g -o2

CC				=	gcc
CFLAGS			=	-Wall -Werror -Wextra -g
RM 				=	rm -rf

###############################################################################
#							 DIRECTORIES AND PATHS						  	  #
###############################################################################

# INCLUDES and LIBRARIES
INCLUDE_DIR		=	includes/

LIBFT_DIR		=	$(INCLUDE_DIR)libft/
LIBFT_H			=	$(LIBFT_DIR)libft.h


SRC_DIR			=	src/

OBJ_DIR		=	obj/

###############################################################################
#							 		FILES								  	  #
###############################################################################

SRC_FILES		=	philo.c 						\
					die_path.c						\
					die_path_utilis.c				\
					ft_routine.c 					\
					ft_routine_utilis.c 			\
					ft_utilis.c 					\
					ft_utilis_thread.c 				\
					ft_thread.c 					\
					ft_atoi.c 						\
					ft_calloc.c 					\
					ft_strlen.c 					\
					ft_isdigit.c 					\
					ft_memset.c 					\

OBJS			=	$(addprefix $(OBJ_DIR), $(OBJ_FILES))
OBJ_FILES		=	$(BUILTIN_FILES:.c=.o) $(SRC_FILES:.c=.o)

HEADER			=	$(addprefix $(INCLUDE_DIR), $(HEADER_F))

VPATH			=	$(SRC_DIR) $(BUILTIN_DIR) 

$(OBJ_DIR)%.o: %.c $(SRC_DIR)
	$(CC) $(CFLAGS) -I $(INCLUDE_DIR) -c $< -g -o $@ -static

###############################################################################
#							 		RECIPES								  	  #
###############################################################################

all:	obj $(NAME)

$(NAME):	$(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

obj:
	mkdir -p $(OBJ_DIR)

leak:		obj $(NAME)
	rm -f report.txt
	@exec 3<>report.txt;valgrind --suppressions=ignore_rdl_leaks.txt --partial-loads-ok=yes --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes --log-fd=3 ./minishell

fd : $(NAME)
	valgrind --track-fds=yes --trace-children=yes ./philo

clean:
	@$(RM) $(OBJS)

fclean:		clean
	@$(RM) $(NAME)
	@$(RM) $(NAME).dSYM*
	@$(RM) $(OBJ_DIR)

re:		fclean all

.PHONY: all clean fclean re leak