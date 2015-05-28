# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eboeuf <eboeuf@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/05 14:57:33 by eboeuf            #+#    #+#              #
#    Updated: 2015/02/12 17:28:50 by eboeuf           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	=		ft_script
SRC		=		main.c pty.c fork.c env.c flags.c display.c
HEADER	=		ft_script.h
OBJ 	=		$(SRC:.c=.o)
CC		=		gcc
CFLAGS	=		-g -Wall -Wextra -Werror
OBJFLAG =		-g -g3 -Wextra -Werror -Wall
LIBDIR	=		libft/
LIB 	=		libft/libft.a

RED		=		\033[33;31m
BLUE	=		\033[33;34m
GREEN	=		\033[33;32m
RESET	=		\033[0m

.PHONY:			all re fclean

all:			$(NAME)

$(LIB):			
				@$(MAKE) -C $(LIBDIR)

$(NAME):		$(LIB) $(OBJ)
					@$(CC) -o $(NAME) $(CFLAGS) $(LIB) $^
					@echo "[$(GREEN)Compilation$(BLUE)$(NAME)$(GREEN)ok$(RESET)]"

%.o: 			%.c
				$(CC) -c -o $@ $(CFLAGS) $^

clean:			
				@cd $(LIBDIR) && $(MAKE) $@
				@rm -f $(OBJ)
				@echo "[$(RED)Supression des .o de $(BLUE)$(NAME)$(GREEN)ok$(RESET)]"

fclean:			clean
				@cd $(LIBDIR) && $(MAKE) $@
				@rm -f $(NAME)
				@echo "[$(RED)Supression de $(BLUE)$(NAME)$(GREEN)ok$(RESET)]"

re:				fclean all
