/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:32:46 by lde-guil          #+#    #+#             */
/*   Updated: 2025/06/27 10:48:59 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/param.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# define DELIMITER "|<>&"
# define ARG_SEP 3;
# define ENV_SEP 2;
# define DELIMITER2 "|&"
# define QUOTES "\'\""
# define NO_ENV "\'\"[]{}!@#%^&*()-=+ "
# define NORMAL 0
# define IN 1
# define OUT 2
# define OUT_APPEND 3
# define HERE_DOC 4
# define ERROR_CHAR ";&():"
# define BUFFER_SIZE 1000
# define BACKUP_PATH "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/bin"

extern pid_t			g_signal_pid;

typedef struct s_split
{
	char				*str;
	int					is_in_quotes;
	int					context;
	struct s_split		*next;
}						t_split;

typedef struct s_split_parse
{
	int					i;
	int					tmp;
	int					dollar;
	char				*buffer;
	int					is_in_quotes;
	int					context;
	int					heredocs;
	t_split				*head;
	t_split				*tail;
}						t_split_parse;

typedef struct s_element
{
	char				*arg;
	char				*token;
	int					position;
	int					env_context;
	struct s_element	*next;
}						t_element;

typedef struct s_list
{
	t_element			*first;
	struct s_list		*next_list;
	int					cmd;
}						t_list;

typedef struct s_token
{
	t_split				*split;
	int					index;
	int					position;
	int					redir;
}						t_token;

typedef struct s_env
{
	char				*name;
	char				*value;
	int					exported;
	struct s_env		*next;
}						t_env;

typedef struct s_cmd
{
	char				*name;
	char				*path;
	char				*heredoc_content;
	char				**args;
	int					is_builtin;
	int					input;
	int					output;
	int					to_exec;
	pid_t				pid;
	struct s_cmd		*prev;
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_pid
{
	pid_t				pid;
	struct s_pid		*next;
}						t_pid;

typedef struct s_exec
{
	t_cmd				*temp_cmd;
	t_cmd				*cmd;
	t_env				*env;
	t_list				*liste;
	int					exit_status;
	int					infile;
	int					heredoc;
	char				*infile_path;
	char				*heredoc_path;
	int					pipe[2];
}						t_exec;

// ______________________BUILTINS________________________
int						ft_cd(t_exec *exec, t_cmd *cmd);
int						ft_echo(t_exec *exec, t_cmd *cmd);
int						ft_env(t_exec *exec);
int						ft_exit(t_cmd *cmd, t_exec *exec);
int						ft_export(t_exec *exec, t_cmd *cmd);
int						ft_pwd(t_exec *exec, t_cmd *cmd);
int						ft_unset(t_exec *exec, t_cmd *cmd);
void					put_error(char *s1, char *s2, char *s3);

void					global_exit(t_exec *exec, int status);
int						export_next(t_cmd *cmd, t_exec *exec);
void					child_hdoc(t_exec *exec, t_element *elem);

// ________________________EXEC__________________________

// ----------------------EXEC CMD------------------------

int						exec_line(t_exec *exec, t_list *list);
int						exec_cmd(t_exec *exec, t_cmd *cmd);
int						exec_builtin(t_exec *ex, t_cmd *cmd);
char					*get_first_arg(t_list *list);
int						fill_cmd(t_list *list, t_exec *exec, t_cmd *cmd);
t_cmd					*assign_cmd(t_list *list, t_exec *exec);
void					add_command(t_exec *exec, t_cmd *cmd);
void					wait_status(t_exec *exec, t_cmd *cmd);
int						is_single_builtin(t_cmd *cmd);
void					exec_single_builtin(t_cmd *cmd, t_exec *exec);

// ------------------------FORK--------------------------
char					**create_args(t_element *elem, t_cmd *cmd);
void					ft_fork(t_exec *exec, t_cmd *cmd);

// ----------------------HEREDOC-------------------------
int						fill_heredoc(t_list *list, t_exec *exec);
int						read_hdoc(t_exec *exec, char *delimit);
void					exit_hdoc(t_exec *exec);

// ______________________ PARSING________________________

//--------------------------SIGNAUX-----------------------
void					signals(void);
void					child_signals(void);
void					hdoc_signals(void);
void					default_sig(void);
void					restore_signals(void);
void					prompt_sig(void);
void					clear_rl_line(void);
void					handle_sigabrt(int code);
void					parent_hdoc(int code);

// -------------------------CORE-------------------------
int						parsing(char *line, t_list *list, t_exec *exec);
int						analyze_line(t_split *split, t_list *list,
							t_exec *exec);

// ----------------------FIND LIST-----------------------
int						handle_env(t_list *list, t_token *token, t_exec *exec);
int						find_builtin(t_list *list, t_token *token);
int						find_cmd(t_list *list, t_token *token);
int						find_files_redir(t_list *list, t_token *token);
void					find_file(t_list *list, int redir, t_token *token);
int						join_path(char **path, t_list *list, t_token *token);
int						is_directory(const char *path);

// ----------------------LIST UTILS----------------------
t_list					*initialisation(void);
void					afficherliste(t_list *liste);
int						add_token(t_list *liste, char *token, t_token *t_token);
void					insertion_list(t_exec *exec, t_list *liste);

// ----------------------- PARSING-----------------------
int						start_parse(t_split *split, t_exec *exec);
int						syntax_error(char *split, int len_split, int position);
int						parse_one_case(char *split);
char					*chr_str(char *str, char *to_find);
t_split					*ft_split_list_minishell(const char *s, t_exec *exec);

// -------------------------UTILS------------------------
int						len_tab(char **split);
int						valid_quote(char *split);
void					free_split(t_split *split);
char					*remove_quotes_around(char *str);
void					empty_string_case(char *split, t_list *list,
							t_token *token);
char					*clean_line(char *line);
int						ft_strchr2(char *str1, char *str2);
int						len_list(t_split *split);
void					init_token(t_token *token);

// ------------------------SPLIT MINISHELL----------------
void					init_split(t_split_parse *split);
void					append_to_list(t_split_parse *split,
							const char *conten);
void					flush_buffer(t_split_parse *split);
void					add_char(t_split_parse *split, char c);
void					handle_dollar_case(const char *s, t_split_parse *split,
							t_exec *exec);
void					handle_quote_case(const char *s, t_split_parse *split,
							t_exec *exec);
void					fill_list(t_split_parse *split, const char *s, char c,
							t_exec *exec);
char					*extract_var_name(const char *s, int *i);

// ------------------------ERROR CASE---------------------
void					error_parsing(char *line, t_exec *exec, t_split *split);

// ________________________UTILS_________________________

// ------------------------ARGS--------------------------
int						is_sep(char c, char sep);
int						is_in_quotes(int position, char *str);
int						get_infile(char *filename, t_cmd *cmd);
int						get_outfile(char *filename, t_cmd *cmd);
int						get_outfile_append(char *filename, t_cmd *cmd);

void					child_process(t_cmd *cmd, int pipe[2], t_exec *exec);
void					parent_process(t_cmd *cmd, int pipe[2]);
void					args_loop(t_element *elem, t_exec *exec, char sep);

// ------------------CREATE ENVIRONMENT------------------
t_env					*create_env(char **envp);
char					*get_var_name(char *str);
char					*get_var_value(char *str);
char					**str_env(t_exec *exec);
void					replace_env(t_list *list, t_exec *exec);
char					*fetch_value(char *name, t_exec *exec);
t_env					*mini_env(void);

// ------------------------FILES-------------------------
int						is_infile(t_element *elem);
int						is_outfile(t_element *elem);
char					*get_file_content(int fd);
void					reopen_io(t_exec *exec);

// ----------------------FIND CMD------------------------
char					*get_cmd_name(char *path);
char					*find_path(char *name, t_exec *exec);

// ------------------------MEMORY------------------------
void					*ft_malloc(size_t nmemb, size_t size, t_exec *exec);
void					exit_malloc_failure(t_exec *exec);

// ---------------------CUSTOM JOIN----------------------
char					*ft_custom_join(char const *s1, char const *s2);
int						is_special_str(char *str);
char					*remove_special_str(char *str);

// ------------------------FREE--------------------------
void					free_tab(char **tab);
void					free_env(t_env *env);
void					ft_free_cmd(t_cmd *cmd);
void					free_exec(t_exec *exec);
void					free_list(t_exec *exec, t_list *liste);

// ------------------------INIT--------------------------
t_exec					*init_exec(char **envp);
t_cmd					*init_cmd(t_list *list, t_exec *exec);
t_cmd					*first_cmd_init(void);
void					compare_cmd_tokens(t_cmd *res, t_element *elem,
							t_exec *exec, t_list *list);
int						assign_loop(t_element *elem, t_list *list, t_exec *exec,
							t_cmd *res);

// ------------------------LIST--------------------------
void					add_end_env(t_env *env, t_env *var);

#endif
