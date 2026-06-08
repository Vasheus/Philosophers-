NAME = philo

SRCFILES = philo_utils.c philo.c  initialize.c monitor.c routine.c setup.c

OBJS = $(SRCFILES:.c=.o)

CC = cc

FLAGS = -Werror -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

%o: %c philo.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all