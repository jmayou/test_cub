NAME = get_next_line.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

 AR = ar -rc

 RM = rm -rf 

src = get_next_line.c get_next_line_utils.c

objc = $(src:.c=.o)

all : $(NAME) 

$(NAME) : $(objc) get_next_line.h
	$(AR) $(NAME) $(objc)

clean :
	$(RM) $(objc)

fclean : clean
	$(RM) $(NAME)

re : fclean all 
	