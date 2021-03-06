# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tevan-de <tevan-de@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/05/24 11:37:21 by tevan-de      #+#    #+#                  #
#    Updated: 2021/06/26 14:52:08 by tevan-de      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CC			=	gcc

CFLAGS		=	-Wall -Werror -Wextra

NAME		=	philo_one

SRCS_PATH	=	./srcs/

SRCS		=	$(SRCS_PATH)check_arguments.c\
				$(SRCS_PATH)check_input.c\
				$(SRCS_PATH)check_philosopher_status.c\
				$(SRCS_PATH)eat_sleep_think_repeat.c\
				$(SRCS_PATH)end_simulation.c\
				$(SRCS_PATH)main.c\
				$(SRCS_PATH)mutex_helpers.c\
				$(SRCS_PATH)mutex_fork.c\
				$(SRCS_PATH)setup_philosophers.c\
				$(SRCS_PATH)setup_simulation.c\
				$(SRCS_PATH)start_simulation.c\
				$(SRCS_PATH)utils_atoi.c\
				$(SRCS_PATH)utils.c

OFILES		=	$(SRCS:%.c=%.o)

INCLUDES	=	-I ./includes/

ifeq ($(DEBUG),1)
	CFLAGS += -g -fsanitize=address
endif

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OFILES)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OFILES) -o $(NAME) -lpthread
	@echo "Executable created..."

%.o: %.c $(INCLUDES)
	@echo "Compiling... $^"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $^ -o $@ -lpthread

clean:
	@echo "Cleaning..."
	@rm -f $(OFILES)

fclean: clean
	@echo "Extra cleaning..."
	@rm -f $(NAME)

re: fclean all
