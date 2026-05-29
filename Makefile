# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/25 19:28:33 by alex              #+#    #+#              #
#    Updated: 2026/05/28 10:41:43 by alejandro        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = test.out
CC = cc
CFLAGS = -Wall -Wextra -Werror
MAIN = test1args.c
RUTA_MAIN = gnl_test/1fd/$(MAIN)

SRCS = src/get_next_line.c src/get_next_line_utils.c \
		$(RUTA_MAIN) \
		
HEADERS = get_next_line.h

all: $(NAME)
	@echo "    _    _     ____    _    ____  ____  ___ _     "
	@echo "   / \\  | |   / ___|  / \\  |  _ \\|  _ \\|_ _| |    "
	@echo "  / _ \\ | |  | |     / _ \\ | |_) | |_) || || |    "
	@echo " / ___ \\| |__| |___ / ___ \\|  _ <|  _ < | || |___ "
	@echo "/_/   \\_\\_____\\____/_/   \\_\\_| \\_\\_| \\_\\___|_____|"
	@echo " Ruta del test (relativa al repo): gnl_test/$(FILE_NAME)/$(MAIN)"
	@echo " Cambia el test: make MAIN=\"el_test_que_quieras.c\""
	@echo " Cambia la carpeta de tests: make FILE_NAME=\"carpeta\""
	
$(NAME): 
	$(CC) $(CFLAGS) -g -I src $(SRCS) -o $(NAME)
	
clean:
	rm $(NAME)
