NAME = minishell

SRCS = src/main.c \
	   src/envp/get_envp_cpy.c \
	   src/shell/handle_shell.c \
	   src/prompt/handle_prompt.c \
	   src/exec/exec_cmds.c src/exec/get_envp_paths.c src/exec/get_cmd_data.c src/exec/handle_pipes.c \
	   src/exec/pipe_it.c \
	   src/parser/store_input.c src/parser/parse_input.c src/parser/get_non_symbol_tokens.c \
	   src/parser/dissociate_args.c src/parser/manage_arg_lst.c src/parser/tokenize_input.c \
	   src/parser/handle_quotes.c src/parser/handle_env_var.c \
	   src/parser/handle_dollar_question_mark.c src/parser/quote_and_dollar_utils.c \
	   src/redirections/handle_redirections.c src/redirections/handle_here_docs.c src/redirections/handle_std_dups.c \
	   src/builtins/handle_builtins.c src/builtins/cd.c src/builtins/echo.c src/builtins/env.c \
	   src/builtins/exit.c src/builtins/export.c src/builtins/get_var_index.c src/builtins/pwd.c \
	   src/builtins/unset.c \
	   src/signals/handle_signals.c src/signals/sig_q.c src/signals/sig_c.c src/signals/sig_d.c \
	   src/errors/handle_syntax_errors.c src/errors/print_err_mess.c \
       utils/ft_strcpy.c utils/ft_strcat.c utils/ft_strlen.c utils/ft_strchr.c utils/ft_strdup.c \
	   utils/ft_strndup.c utils/ft_strcmp.c utils/ft_bzero.c  utils/ft_calloc.c utils/ft_split.c \
	   utils/ft_print_double_char.c utils/ft_print_triple_char.c utils/ft_strrchr.c \
	   utils/ft_strjoin.c utils/ft_print_arg.c utils/ft_putstr_fd.c utils/ft_putchar_fd.c utils/ft_putnbr_fd.c \
	   utils/ft_get_next_line.c utils/ft_strcat_gnl.c utils/ft_isalpha.c utils/ft_isdigit.c \
	   utils/is_c.c utils/ft_itoa.c utils/is_whitespace.c utils/ft_atollu.c

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror -g -I includes

all: $(NAME)

$(NAME): $(OBJS)
	cc $(CFLAGS) $(OBJS) -o $(NAME) -lreadline -lhistory -lncurses

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
