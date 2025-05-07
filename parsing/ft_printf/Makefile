NAME = libftprintf.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

 AR = ar -rc

 RM = rm -rf 

src = ft_put_adrs.c ft_putnbr.c ft_unsnbr.c\
ft_printf.c ft_putchar.c ft_putopper_hexa.c ft_putlower_hexa.c ft_putstr.c
objc = $(src:.c=.o)

all : $(NAME) 

$(NAME) : $(objc) ft_printf.h
	$(AR) $(NAME) $(objc)

clean :
	$(RM) $(objc)

fclean : clean
	$(RM) $(NAME)

re : fclean all 
	