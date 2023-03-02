SRCS = $(addprefix srcs/, \
	main.c \
	$(addprefix philosophers/, \
	philo_routine.c \
	philo_init.c) \
	$(addprefix monitors/, \
	philosopher_monitor.c) \
	$(addprefix utils/, \
	checking_args.c \
	chronology.c \
	finish.c \
	print_message.c \
	state_manager.c)) \
	$(addprefix utilitaries/, \
	ft_atol.c \
	ft_split.c \
	ft_strdup.c \
	ft_strlen.c \
	ft_freetab.c)

HEADER = include/philosopher.h
RM = rm -rf
NAME = philo
CC = gcc $(CFLAGS)

OBJECTS = $(subst srcs/,srcs/build/,$(subst utilitaries/,utilitaries/build/,$(SRCS:.c=.o)))
DEPEND = ${OBJECTS:.o=.d}

CFLAGS = -Wall -Werror -Wextra -lpthread -pthread

all: $(NAME)

${NAME}: $(OBJECTS)
	$(CC) -o $(NAME) $(OBJECTS)

-include $(DEPEND)

utilitaries/build/%.o: utilitaries/%.c
	@mkdir -p $(@D)
	$(CC) -MMD -c $< -o $@

srcs/build/%.o: srcs/%.c
	@mkdir -p $(@D)
	$(CC) -MMD -c $< -o $@

clean:
	$(RM) $(OBJECTS) $(DEPEND)
	$(RM) srcs/build utilitaries/build

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
