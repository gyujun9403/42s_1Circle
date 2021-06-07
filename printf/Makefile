GCC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = printf.a
SRCS = ./ft_printf.c ./pf_putnbr_fd.c
SRCS_LIBFT = ./libft/ft_bzro.c ./libft/ft_putchar_fd.c ./libft/ft_putnbr_fd.c ./libft/ft_putstr_fd.c
OBJS = $(SRCS:.c=.o)
INCLUDE = -I ./ft_printf.h
INCLUDE_LIBFT = -I ./libft/libft.h

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