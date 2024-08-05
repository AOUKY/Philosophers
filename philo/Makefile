NAME  = philo
SRCS  = philo.c tools.c tools2.c thread.c thread2.c
HEDER = philo.h
OBJS  = ${SRCS:.c=.o}
CC    = cc
CFLAGS = -Wall -Werror -Wextra 

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

%.o: %.c $(HEDER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
