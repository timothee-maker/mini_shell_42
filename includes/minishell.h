/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:32:46 by lde-guil          #+#    #+#             */
/*   Updated: 2025/05/13 14:08:24 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h> 
# include <termios.h>
# include <dirent.h>
# include <sys/param.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# define DELIMITER "|<>&"
# define DELIMITER2 "|&"
# define QUOTES "\'\""
# define NO_ENV "\'\"[]{} "
# define NORMAL 0
# define IN 1
# define OUT 2
# define OUT_APPEND 3
# define HERE_DOC 4
# define ERROR_CHAR ";&():"
# define BUFFER_SIZE 1000

extern pid_t	g_pid;

typedef struct s_element
{
	char				*arg;
	char				*token;
	int					position;
	struct s_element	*next;
}	t_element;

typedef struct s_list
{
	t_element		*first;
	struct s_list	*next_list;
	int				cmd;
}	t_list;

typedef struct s_env
{
	char			*name;
	char			*value;
    int             exported;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
	char 		*name;
	char 		*path;
    char        **args;
	int			is_builtin;
    int         input;
    int         output;
    pid_t        pid;
    struct s_cmd    *prev;
    struct s_cmd    *next;
}	t_cmd;

typedef struct s_pid
{
    pid_t           pid;
    struct s_pid    *next;
}   t_pid;

typedef struct s_exec
{
	t_cmd	*cmd;
	t_env 	*env;
    int     exit_status;
    int     infile;
    int     heredoc;
    char     *infile_path;
    char     *heredoc_path;
    int     pipe[2];
}	t_exec;

// ______________________BUILTINS________________________
int     ft_cd(t_exec *exec, t_cmd *cmd);
int     ft_echo(t_cmd *cmd);
int     ft_env(t_exec *exec);
int     ft_exit(t_cmd *cmd);
int     ft_export(t_exec *exec, t_cmd *cmd);
int     ft_pwd(t_cmd *cmd);
int     ft_unset(t_exec *exec, t_cmd *cmd);

int     home_case(t_exec *exec, t_env *var);
int     reverse_case(t_exec *exec, t_env *var);
int     base_case(t_env *var, char **args);
int     update_currpwd(t_env *var, char *path);
int     update_oldpwd(t_env *var);
void    global_exit(t_exec *exec);


// ________________________EXEC__________________________

// ----------------------EXEC CMD------------------------
void    exec_line(t_exec *exec, t_list *list);
int     exec_cmd(t_exec *exec, t_cmd *cmd);
int     exec_builtin(t_exec *ex, t_cmd *cmd);
char    *get_first_arg(t_list *list);
t_cmd   *assign_cmd(t_list *list, t_exec *exec);
void    add_command(t_exec *exec, t_cmd *cmd);
void    wait_status(t_exec *exec, t_cmd *cmd);

// ------------------------FORK--------------------------
char    **create_args(t_exec *exec);
void    ft_fork(t_exec *exec, t_cmd *cmd);

// ----------------------HEREDOC-------------------------
void 	fill_heredoc(t_list *list, t_exec *exec);


// ______________________ PARSING________________________

//--------------------------SIGNAUX-----------------------
void 	handle_sigint(int sig);

// -------------------------CORE-------------------------
int		parsing(char	*line, t_list *list);
int		analyze_line(char **split, t_list *list);

// ----------------------FIND LIST-----------------------
int	    find_builtin(char *new_str, t_list *list, int index);
int	    find_cmd(char *split, t_list *list, int index, char *new_str);
int	    find_files_redir(char *split, t_list *list, int index, char *new_str);
void	find_file(char *split, t_list *list, int index, int redir);
//void	find_opt_arg(char *split, t_list *list, int index);

// ----------------------LIST UTILS----------------------
t_list	*initialisation(void);
void	afficherliste(t_list *liste);
int		add_token(t_list *liste, char *arg, char *token, int index);
void	destruction(t_list *liste);
void	insertion_list(t_list *liste);

// ----------------------- PARSING-----------------------
int		start_parse(char **split);
int		syntax_error(char *split, int len_split, int position);
int	    parse_one_case(char *split);
char	*chr_str(char *str, char *to_find);
char	**ft_split_minishell(char const *s, char c);

// -------------------------UTILS------------------------
int	    len_tab(char **split);
int	    valid_quote(char *split);
void    free_split(char **split);
char	*remove_quotes(char *str);
char	*remove_quotes_around(char *str);
void	empty_string_case(char *split, t_list *list, int index);
char	*clean_line(char *line);
int		ft_strchr2(char *str1, char *str2);
int		check_valid_dollar(char *split);


// ________________________UTILS_________________________

// ------------------------ARGS--------------------------
void    fill_args(t_list *list, t_exec *exec, t_cmd *cmd);
int		is_sep(char c, char sep);
void    get_infile(char *filename, t_cmd *cmd);
void    get_outfile(char *filename, t_cmd *cmd);

void    child_process(t_cmd *cmd, int pipe[2], t_exec *exec);
void    parent_process(t_cmd *cmd, int pipe[2]);

// ------------------CREATE ENVIRONMENT------------------
t_env	*create_env(char **envp);
char	*get_var_name(char *str);
char	*get_var_value(char *str);
char    **str_env(t_exec *exec);
void    replace_env(t_list *list, t_exec *exec);
char    *fetch_value(char *name, t_exec *exec);

// ------------------------FILES-------------------------
int 	is_infile(t_element *elem);
int 	is_outfile(t_element *elem);
char 	*get_file_content(int fd);

// ----------------------FIND CMD------------------------
char    *get_cmd_name(char *path);
char    *find_path(char *name, t_exec *exec);

// ---------------------CUSTOM JOIN----------------------
char	*ft_custom_join(char const *s1, char const *s2);

// ------------------------FREE--------------------------
void    free_tab(char **tab);
void    free_env(t_env *env);
void    ft_free_cmd(t_cmd *cmd);
void    free_exec(t_exec *exec);

// ------------------------INIT--------------------------
t_exec 	*init_exec(char **envp);
t_cmd 	*init_cmd(t_list *list, t_exec *exec);

#endif
