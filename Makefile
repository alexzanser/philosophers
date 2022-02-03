NAME = philo
BONUS_NAME = bonus
#
SOURSE = philo_m/actions.c philo_m/checkers.c philo_m/init.c \
		philo_m/philo.c philo_m/utils.c

BONUS_SOURSE = 	philo_b/actions_bonus.c philo_b/checkers_bonus.c\
				philo_b/init_bonus.c philo_b/philo_bonus.c philo_b/utils_bonus.c
#
CFLAGS		= -Wall -Werror -Wextra -I
CC = gcc
#
HEADER	= philo_m/philo.h
BONUS_HEADER = philo_b/philo_bonus.h
#
OBJ = $(SOURSE:%.c=%.o)
BONUS_OBJ = $(BONUS_SOURSE:%.c=%.o)
#
.PHONY : all clean fclean re
#
all : $(NAME)
#
$(NAME) :  $(SOURSE) $(HEADER)
	$(CC) $(CFLAGS) $(HEADER) $(SOURSE) -o $(NAME)
#
%.o :	%.c $(HEADER)
	$(CC) $(CFLAGS) $(HEADER) -c $< -o $@
#
bonus :		$(BONUS_SOURSE) $(BONUS_HEADER)
	$(CC) $(CFLAGS) $(BONUS_HEADER) $(BONUS_SOURSE) -o $(BONUS_NAME)
#
clean :
	@rm -f $(OBJ) $(BONUS_OBJ)
#
fclean : clean
	@rm -f $(NAME) $(BONUS_NAME)
#
re : fclean all
