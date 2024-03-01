### VAR ###

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -O0


ARCH := $(shell uname -m)
ifeq ($(ARCH), x86_64)
	RLDIR = $(shell brew --prefix readline)
else
    RLDIR = /opt/homebrew/opt/readline
endif

SRCS_MAIN		= srcs/main.c srcs/error.c srcs/init_signal.c \
					srcs/memory_utils.c srcs/env.c
SRCS_LEXER		= srcs/lexer/lexer_utils.c srcs/lexer/lexer.c
SRCS_PARSER		= srcs/parser/expand.c srcs/parser/node_constructor.c srcs/parser/parse_argv.c \
					srcs/parser/parse_cmd.c srcs/parser/parse_helper.c srcs/parser/parse_here_doc.c \
					srcs/parser/parse_io_redirect.c srcs/parser/parse_main.c srcs/parser/parse_pipeline.c \
					srcs/parser/parse_redirect.c srcs/parser/parse_simple_cmd.c srcs/parser/parse_utils.c \
					srcs/parser/expand_utils.c srcs/parser/expand_helper.c
SRCS_EXECUTION	= srcs/execution/execute.c srcs/execution/execute_utils.c srcs/execution/parse_env.c \
					srcs/execution/redirect.c srcs/execution/redirect_utils.c
SRCS_BUILTIN	= srcs/builtin/env.c
SRCS_LIB_EX		= srcs/libft_extended/ft_realloc.c
SRCS_UTIL		= srcs/util/get_args.c
SRCS = ${SRCS_MAIN} ${SRCS_LEXER} ${SRCS_PARSER} ${SRCS_EXECUTION} ${SRCS_LIB_EX} ${SRCS_UTIL}

OBJS = $(SRCS:%.c=%.o)

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(INPUTRC)
	$(CC) $(CFLAGS) -lft -Llibft -lreadline -L $(RLDIR)/lib -I $(RLDIR)/include -o $(NAME) $(OBJS)

$(LIBFT) :
	$(MAKE) -j3 -C libft

.c.o :
		$(CC) $(CFLAGS) -c -I $(RLDIR)/include $< -o $@

clean:
		rm -rf $(OBJS)
		@$(MAKE) -C libft clean

fclean: clean
		rm -rf $(NAME) $(LIBFT)

re: fclean all

.phony: all clean fclean re