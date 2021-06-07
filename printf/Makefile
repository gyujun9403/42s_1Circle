GCC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = libftprintf.a
SRCS = ./ft_printf.c ./libft/*.c
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
INCLUDE = -I ./ft_printf.h

all : $(NAME)

%.o : %.c
	$(GCC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME) : $(OBJS)
	ar rcs $@ $^

clean : 
	rm -f $(OBJS) $(OBJS_BONUS)

fclean : 
	rm -f $(NAME)

re : fclean all

bonus : $(OBJS_BONUS)
	ar rcs $(NAME) $^

.PHONY : all clean fclean re bonus