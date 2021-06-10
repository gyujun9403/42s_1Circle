CC			= gcc
CFLAGS		= -Wall -Wextra -Werror

NAME		= ./libftprintf.a
LIBFT		= libft
LIBFT_LIB	= libft.a
SRCS_LIBFT	= ./$(LIBFT)/ft_bzero.c \
	./$(LIBFT)/ft_isdigit.c \
	./$(LIBFT)/ft_isprint.c \
	./$(LIBFT)/ft_putchar_fd.c \
	./$(LIBFT)/ft_putstr_fd.c \
	./$(LIBFT)/ft_strlen.c
OBJS_LIBFT = $(SRCS_LIBFT:.c=.o)

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

$(NAME) : $(OBJS) $(OBJS_LIBFT)
	ar rc $(LIBFT)/$(LIBFT_LIB) $(OBJS_LIBFT)
	cp $(LIBFT)/$(LIBFT_LIB) $(NAME)
	ar rc $(NAME) $(OBJS)

all : $(NAME)

fclean : clean
	rm -f $(NAME)
	rm -f $(LIBFT)/$(LIBFT_LIB)

clean :
	rm -f $(OBJS)
	rm -f $(OBJS_LIBFT)

re : fclean all

.POHNY : all fclean clean re
