CC				= cc 
RM				= rm -f
CFLAGS			= -Wextra -Wall -Werror -g3
PHILO_NAME 		= philo
PHILO_SRCS		= src/main.c src/parsing.c src/init.c src/routine.c src/utils.c src/monitor.c
PHILO_OBJS 		= $(PHILO_SRCS:.c=.o)

all:			$(PHILO_NAME)

$(PHILO_NAME):	$(PHILO_OBJS)
					$(CC) -o $(PHILO_NAME) $(PHILO_SRCS) $(CFLAGS)

clean:
				$(RM) $(PHILO_OBJS)

fclean:	 		clean
				$(RM) $(PHILO_NAME)

re:				fclean all

.PHONY:			all clean fclean re