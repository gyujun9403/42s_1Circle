CC			= gcc
CFLAGS		= -Wall -Wextra -Werror

NAME		= libftprintf.a
LIBFT		= libft
LIBFT_LIB	= libft.a

SRCS		= ./ft_printf.c\
			  ./utils.c\
			  ./char_n_string.c\
			  ./dec_n_int.c\
			  ./unsigned_int.c\
			  ./hex.c\
			  ./pointer.c\
			  ./ampersand.c
OBJS		= $(SRCS:.c=.o)
INCS		= ./

.c.o :
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -I $(INCS)

$(NAME) : $(OBJS)
	make all -C $(LIBFT)/
	cp $(LIBFT)/$(LIBFT_LIB) $(NAME)
	ar rc $(NAME) $(OBJS)

all : $(NAME)

fclean : clean
	rm -f $(NAME)
	make fclean -C $(LIBFT)

clean :
	rm -f $(OBJS)
	make clean -C $(LIBFT)

re : fclean all

.POHNY : all fclean clean re