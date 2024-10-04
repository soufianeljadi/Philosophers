
NAME = philosophers

# The Helgrind thread error detection tool with which we can run our program, like this: 
# 	valgrind --tool=helgrind
# The DRD thread error detection tool, which is also launched at runtime like this: 
# 	valgrind --tool=drd
# gcc -fsanitize=thread -g

CC = cc -Wall -Wextra -Werror -fsanitize=address -g

SRC =	philosophers.c \
		utils.c \
		data_init.c \
		parse_input.c \
		dinner_start.c \

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