/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: debian <debian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 00:31:30 by rgrochow          #+#    #+#             */
/*   Updated: 2024/09/20 05:50:06 by debian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>

/* RETURN status */
# define SUCCESS 0
# define FAILURE 1

/* DOLLAR & QUOTE status */
# define NO_HANDLED 0
# define HANDLED 1
# define HANDLED_BUT_EMPTY 2

/* Exit codes */

# define EC_SUCCESS 0
# define EC_ARG_E 1
# define EC_MALLOC_E 1
# define EC_FORK_E 1
# define EC_FD_E 1
# define EC_DUP_E 1
# define EC_HD_E 1
# define EC_CMD_E 127

/* Error messages */
# define E_USAGE "Usage: "
# define E_BASH "bash: "
# define E_BASH_CD "bash: cd: "
# define E_EXPORT "export: `"
# define E_UNV_ID "': not a valid identifier"
# define E_MANY_ARG "too many arguments"
# define E_SYNT_ERR "syntax error near unexpected token `"
# define E_UNEX_CMD ": command not found"
# define E_NUM_ARG_REQ ": numeric argument required"

/* For GNL function */
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

extern int	g_signal_value;

typedef struct s_arg
{
	int				index;
	char			type[50];
	char			*value;
	int				pipe_scope;
	int				pipe_nb;
	int				is_builtin;
	int				quote_status_arg;
	int				dollar_status_arg;
	char			**arg_lst;
	char			*cmd_path;
	char			*here_doc;
	struct s_arg	*next;
	struct s_arg	*prev;
}	t_arg;

typedef struct s_shell
{
	char	*prompt;
	char	*input;
	char	**argv;
	int		quote_status_shell;
	int		dollar_status_shell;
	t_arg	*arg;
	char	**envp_cpy;
	char	**envp_paths;
	int		argc;
	int		cmd_flag;
	int		cmd_count;
	pid_t	*child_pid;
	int		pipe_count;
	int		**pipe_fd;
	int		active_child;
	int		exit_status;
	int		hd_interrupted;
}	t_shell;

/* ************************************************************************** */
/*                                    SHELL                                   */
/* ************************************************************************** */
/* src/shell/handle_shell.c */
void					init_shell(t_shell *shell);
void					clean_shell_within_rl(t_shell *shell);
void					clean_shell_out_rl(t_shell *shell);
void					free_double_char(char **tab);
void					clean_prompt(t_shell *shell);

/* ************************************************************************** */
/*                                    ENVP                                   */
/* ************************************************************************** */
/* src/envp/get_envp_cpy.c */
void					get_envp_cpy(t_shell *shell, char **envp);
int						get_envp_len(char **envp);

/* ************************************************************************** */
/*                                   SIGNALS                                  */
/* ************************************************************************** */
/* src/signals/handle_signals.c */
void					signal_handlers(void);
void					signal_handlers_interactive(void);
/* src/signals/sig_q.c */
void					handle_sigquit(int sig);
/* src/signals/sig_c.c */
void					handle_sigint(int sig);
void					handle_sigint_interactive(int sig);
/* src/signals/sig_d.c */
void					handle_eof(t_shell *shell);

/* ************************************************************************** */
/*                                    PROMPT                                  */
/* ************************************************************************** */
/* src/prompt/handle_prompt.c */
char					*build_prompt(void);

/* ************************************************************************** */
/*                                    PARSER                                  */
/* ************************************************************************** */
/* src/parser/store_input.c */
void					store_input(t_shell *shell, char *input);
int						is_whitespace(char c);
void					dissociate_args(t_shell *shell);
/* src/parser/handle_quotes.c */
char					*handle_quotes(char *argv_i, t_shell *shell);
int						incr_quote_flag(char *argv_i, int j, int d_quote,
							int s_quote);
/* src/parser/handle_env_var.c */
char					*handle_env_var(char *argv_i, t_shell *shell);
/* src/parser/quote_and_dollar_utils.c */
int						incr_s_quote_flag(char *argv_i, int j, int d_quote,
							int s_quote);
int						incr_d_quote_flag(char *argv_i, int j, int d_quote,
							int s_quote);
int						should_dollar_be_exp(char *argv_i, int j, int s_quote);
void					update_dollar_flag(char *exp_argv_i, t_shell *shell);
void					get_dollar_and_quote_status(t_arg *new_node,
							t_shell *shell);
/* src/parser/handle_dollar_question_mark.c */
char					*get_exit_code(t_shell *shell);
/* src/parser/parse_input.c */
int						parse_input(t_shell *shell, char *input);
/* src/parser/manage_arg_lst.c */
void					init_arg_with_value(t_shell *shell);
t_arg					*ft_lstnew(t_shell *shell, char *arg);
void					ft_lstadd_next(t_arg *cur, t_arg *new, t_arg *next);
void					free_arg_lst(t_arg *arg);
/* src/parser/dissociate_args.c */
int						is_double_symbol(t_arg *current, int i);
int						is_single_symbol(t_arg *current, int i);
int						add_new_node(t_shell *shell, t_arg *current,
							int i, int nb);
/* src/parser/tokenize_input.c */
void					tokenize_input(t_shell *shell);
/* src/parser/get_non_symbol_tokens.c */
void					is_cmd_arg(t_arg *current, t_shell *shell);
void					is_fd(t_arg *current);
void					is_cmd(t_arg *current, t_shell *shell);
void					is_limiter(t_arg *current, t_shell *shell);

/* ************************************************************************** */
/*                                     EXEC                                   */
/* ************************************************************************** */
/* src/exec/exec_cmds.c */
void					exec_cmds(t_shell *shell);
void					exec_cmd(t_shell *shell, t_arg *cur_cmd);
t_arg					*get_cmd(t_shell *shell, int i);
/* src/exec/get_envp_paths.c */
void					get_envp_paths(t_shell *shell);
/* src/exec/get_cmd_data.c */
void					get_cmd_data(t_shell *shell);
/* src/exec/handle_pipes.c */
void					init_pipes(t_shell *shell);
void					free_pipe_fd(t_shell *shell);
void					close_pipe_fd(t_shell *shell);
void					init_child_pid(t_shell *shell);
void					get_pipe_count(t_shell *shell);
/* src/exec/pipe_it.c */
void					pipe_it(t_shell *shell);
int						get_pipe_index(t_shell *shell, t_arg *cur_cmd,
							char *std);

/* ************************************************************************** */
/*                                 REDIRECTIONS                               */
/* ************************************************************************** */
/* src/redirections/handle_redirections.c */
void					handle_input_redir(t_shell *shell, t_arg *cur_cmd);
void					handle_output_redir_pipe(t_shell *shell,
							t_arg *cur_cmd);
t_arg					*get_start_pipe(t_arg *cur_cmd);
/* src/redirections/handle_std_dups.c */
void					dup_stdin_to_infile(t_shell *shell, char *filename);
void					dup_stdin_to_fd0(t_shell *shell, t_arg *cur_cmd);
void					dup_stdout_to_outfile(t_shell *shell, char *outfile,
							char *symbol);
void					dup_stdout_to_fd1(t_shell *shell, t_arg *cur_cmd);
/* src/redirections/handle_here_docs.c */
int						open_fd(char *fd_name, char *options, t_shell *shell);
void					handle_here_docs(t_shell *shell);
void					del_here_docs(t_shell *shell);

/* ************************************************************************** */
/*                                   BUILTINS                                 */
/* ************************************************************************** */
/* src/builtins/handle_builtins.c */
void					exec_builtin(t_arg *cmd, t_shell *shell, int fd);
int						check_inv_fds(t_arg *single_cmd, t_shell *shell);
int						handle_output_redir_builtin(t_arg *single_cmd,
							t_shell *shell);
t_arg					*get_end_pipe(t_arg *cur_cmd);
/* src/builtins/cd.c */
void					exec_cd(t_shell *shell, t_arg *cmd);
/* src/builtins/echo.c */
void					exec_echo(t_shell *shell, t_arg *cur_cmd, int fd);
/* src/builtins/exit.c */
void					exec_exit(t_shell *shell, t_arg *cur_cmd,
							int exit_code);
/* src/builtins/pwd.c */
void					exec_pwd(t_shell *shell, int fd);
/* src/builtins/env.c */
void					exec_env(t_shell *shell, int declare, int fd);
/* src/builtins/get_var_index.c */
int						get_var_index(t_shell *shell, char *s, char c);
int						get_var_name_len(char *s, char c);
/* src/builtins/export.c */
void					exec_export(t_shell *shell, t_arg *cur_cmd, int fd);
/* src/builtins/unset.c */
void					exec_unset(t_shell *shell, t_arg *cur_cmd);

/* ************************************************************************** */
/*                                   ERRORS                                   */
/* ************************************************************************** */
/* src/errors/handle_syntax_errors.c */
int						handle_syntax_errors(t_shell *shell);
/* src/errors/print_err_mess.c */
void					print_err_mess(char *s1, char *s2, char *s3,
							t_shell *shell);
void					print_err_mess_cd(char *s1, char *s2, char *s3,
							t_shell *shell);

/* ************************************************************************** */
/*                                    UTILS                                   */
/* ************************************************************************** */
size_t					ft_strlen(const char *s);
char					*ft_strcpy(char *dest, const char *src);
char					*ft_strcat(char *dest, const char *src);
char					*ft_strchr(const char *s, int c);
char					*ft_strdup(char *s1);
char					*ft_strndup(char *s, size_t n, t_shell *shell);
int						ft_strcmp(const char *s1, const char *s2);
void					ft_bzero(void *s, size_t n);
void					*ft_calloc(size_t count, size_t size);
char					**ft_split(char const *s, char c);
void					ft_print_double_char(char **tab, char *lines_name);
void					ft_print_triple_char(char ***tab, char *lines_name);
char					*ft_strrchr(const char *s, int c);
char					*ft_strjoin(char *s1, int free_s1, char *s2,
							int free_s2);
void					ft_print_arg(t_arg *t_arg);
void					ft_putstr_fd(char *s, int fd);
void					ft_putchar_fd(char c, int fd);
void					ft_putnbr_fd(int n, int fd);
char					*ft_get_next_line(int fd);
char					*ft_strcat_gnl(char *dest, char *src, int read_bytes);
int						ft_isalpha(int c);
int						ft_isdigit(int c);
int						is_c(char *s, char c, int start_i);
char					*ft_itoa(int n);
int						is_whitespace(char c);
unsigned long long int	ft_atollu(const char *str);

#endif
