
NAME = philo

CC = cc -Wall -Wextra -Werror #-fsanitize=thread -g

SRC =	philosophers.c \
		init_data.c \
		utils.c \
		dinner_start.c

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

all: $(NAME)

%.o : %.c philosophers.h
	@$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all