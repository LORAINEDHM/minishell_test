NAME = gnl.a

SRCS = get_next_line.c get_next_line_utils.c


HEADER = ./

CFLAGS = -Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

%.o: %.c
	gcc $(CFLAGS) -c -I$(HEADER) -o $@ $<

clean: 
	/bin/rm -f $(OBJS) 

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus