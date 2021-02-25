#################
##  VARIABLES  ##
#################

#	Sources

SRCS = $(SRCSDIR)/main.c $(SRCSDIR)/init.c $(SRCSDIR)/exit.c $(SRCSDIR)/free.c $(SRCSDIR)/display.c $(SRCSDIR)/utils.c \
		$(SRCSDIR)/builtins/pwd.c $(SRCSDIR)/quotes.c $(SRCSDIR)/parsing/remove_quotes.c \
		$(SRCSDIR)/path.c $(SRCSDIR)/error.c $(SRCSDIR)/parsing/slash.c $(SRCSDIR)/parsing/token.c $(SRCSDIR)/parsing/token1.c\
		$(SRCSDIR)/parsing/pipe.c $(SRCSDIR)/token_utils.c $(SRCSDIR)/parsing/semicolon.c $(SRCSDIR)/parsing/utils.c \
		$(SRCSDIR)/parsing/token2.c $(SRCSDIR)/parsing/parsing.c $(SRCSDIR)/parsing/dollar.c $(SRCSDIR)/program/fork.c $(SRCSDIR)/commands/execute.c \
		$(SRCSDIR)/builtins/builtins.c $(SRCSDIR)/builtins/echo.c $(SRCSDIR)/program/redirections.c $(SRCSDIR)/program/redirections2.c \
		$(SRCSDIR)/builtins/export.c $(SRCSDIR)/builtins/unset.c $(SRCSDIR)/builtins/cd.c $(SRCSDIR)/builtins/env.c
SRCSDIR = ./srcs

#	Objects

OBJS = $(SRCS:.c=.o)

#	Headers

HEADER = minishell.h
HEADERDIR = ./srcs

#	Libraries

LIBFTDIR = ./libs/libft
LIBFT = libft.a
GNLDIR = ./libs/GNL
GNL = gnl.a

#	Name

NAME = minishell

#	Compiler

CC = gcc

#	Flags

CFLAGS = 
# -Wall -Werror -Wextra 


###############
##  TARGETS  ##
###############

all: $(NAME)

# -fsanitize=address 
# $(NAME): $(OBJS) $(LIBFT) $(GNL)
# 	@$(CC) -fsanitize=address -I$(HEADERDIR)/ $(OBJS) $(LIBFTDIR)/$(LIBFT) $(GNLDIR)/$(GNL) -o $(NAME)
# 	@echo "minishell compiled succesfully"

$(NAME): $(OBJS) $(LIBFT) $(GNL)
	@$(CC) -I$(HEADERDIR)/ $(OBJS) $(LIBFTDIR)/$(LIBFT) $(GNLDIR)/$(GNL) -o $(NAME)
	@echo "minishell compiled succesfully"
	
$(SRCSDIR)/%.o: %.c $(SRCSDIR)/$(HEADER)
	@$(CC) $(CFLAGS) -g -c -o $@ $< 

# .PHONY: leaks
# leaks: CC = /usr/local/opt/llvm/bin/clang
# leaks: CFLAGS += -mlinker-version=450  -g
# leaks: fclean $(NAME)
# 		ASAN_OPTIONS=detect_leaks=1 ./$(NAME)

clean: 
	/bin/rm -f $(OBJS) $(LIBFTDIR)/*.o $(GNLDIR)/*.o 

fclean: clean
	/bin/rm -f $(NAME) $(LIBFTDIR)/$(LIBFT) $(GNLDIR)/$(GNL)

re: fclean all

$(LIBFT):	
			@cd ${LIBFTDIR} && make
			@echo "libft compiled succesfully"

$(GNL):	
			@cd ${GNLDIR} && make
			@echo "get_next_line compiled succesfully"

.PHONY: all clean fclean re