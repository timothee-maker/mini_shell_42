/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:32:46 by lde-guil          #+#    #+#             */
/*   Updated: 2025/04/17 17:21:02 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
#include <signal.h> 
# include <termios.h>
# include <linux/limits.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# define DELIMITER "|<>&"
# define QUOTES "\'\""
# define NORMAL 0
# define IN 1
# define OUT 2
# define OUT_APPEND 3
# define HERE_DOC 4
# define ERROR_CHAR "<>|&"
# define BUFFER_SIZE 1000

/*lignes test*/
// <Makefile "/"usr""/bin/""ls"|grep a|cat>"/""dev/""stdout"|"e""c""h""o" "'hola que tal' $ZSH okay"
// cas defaillant : ls -la > outfile1 > outfile2 | grep < outfile3 > outfile2

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
	struct s_env	*next;
}	t_env;

typedef struct s_filenode
{
	char				*name;
	int					open_mode;
	struct s_filenode 	*next;
}	t_filenode;

typedef struct s_cmd
{
	char 		*name;
	char 		*path;
	char		*delimit;
	int			is_builtin;
    int         is_pipe;
	t_filenode 	*infiles;
	t_filenode 	*outfiles;
}	t_cmd;

typedef struct s_exec
{
	t_cmd	*cmd;
	t_env 	*env;
    int     exit_status;
	int		infile;
	int		outfile;
    int     fstdin;
    char    *infile_path;
    char    *outfile_path;
    char    *fstdin_path;
}	t_exec;

// ______________________BUILTINS________________________
void    ft_cd(t_exec *exec);
void    ft_echo(t_exec *exec);
void    ft_env(t_exec *exec);
void    ft_exit(t_exec *exec);
void    ft_export(t_exec *exec);
void    ft_pwd(void);
void    ft_unset(t_exec *exec);

// ________________________EXEC__________________________

// ----------------------EXEC CMD------------------------
void    exec_line(t_exec *exec, t_list *list);
void    exec_cmd(t_exec *exec);
void    exec_builtin(t_exec *ex);

// ------------------------FORK--------------------------
void    child_process(t_exec *exec);
void    parent_process(pid_t pid, t_exec *exec);
char    **create_args(t_exec *exec);

// ----------------------HEREDOC-------------------------
void 	fill_heredoc(t_list *list, t_exec *exec);

// -----------------------OUTPUT-------------------------
void    display_output(t_exec *exec);
void    redirect_output(t_exec *exec);
void    ft_pipe(t_exec *exec, char *output);

// _______________________UTILS__________________________

// ------------------------ARGS--------------------------
void 	fill_args(t_list *list, t_exec *exec);
int		is_sep(char c, char sep);

// ------------------CREATE ENVIRONMENT------------------
t_env	*create_env(char **envp);
char	*get_var_name(char *str);
char	*get_var_value(char *str);
char    **str_env(t_exec *exec);
void    replace_env(t_list *list, t_exec *exec);

// ------------------------FILES-------------------------
int 	is_infile(t_element *elem);
int 	is_outfile(t_element *elem);
int 	get_open_mode(t_element *elem);
char 	*get_file_content(int fd);
void    ft_reopen_IO(t_exec *exec, int IO);

// -----------------------FILES2-------------------------
void    clear_IO(t_exec *exec, int IO);
int     is_stdin_empty(t_exec *exec);

// ----------------------FIND CMD------------------------
char    *get_cmd_name(char *path);

// ------------------------FREE--------------------------
void    free_tab(char **tab);
void    free_env(t_env *env);
void    free_filenode(t_filenode *fnode);
void    free_cmd(t_cmd *cmd);
void    free_exec(t_exec *exec);

// ------------------------INIT--------------------------
t_exec 		*init_exec(char **envp);
t_cmd 		*init_cmd(t_list *list);
t_filenode 	*init_infiles(t_list *list);
t_filenode 	*init_outfiles(t_list *list);

// ______________________ PARSING________________________

//--------------------------SIGNAUX-----------------------
void 	handle_sigint(int sig);

// -------------------------CORE-------------------------
void	minishell(char	*line, t_list *list);
void	analyze_line(char **split, t_list *list);

// ----------------------FIND LIST-----------------------
int	    find_builtin(char *split, t_list *list, int index);
int	    find_cmd(char *split, t_list *list, int index);
int	    find_files_redir(char *split, t_list *list, int index);
void	find_file(char *split, t_list *list, int index, int redir);
void	find_opt_arg(char *split, t_list *list, int index);

// ----------------------LIST UTILS----------------------
t_list	*initialisation(void);
void	afficherliste(t_list *liste);
void	add_token(t_list *liste, char *arg, char *token, int index);
void	destruction(t_list *liste);
void	insertion_list(t_list *liste);

// ----------------------- PARSING-----------------------
int		start_parse(char **split);
int		syntax_error(char **split, int len_split);
int	    parse_one_case(char *split);
char	*chr_str(char *str, char *to_find);
char	**ft_split_minishell(char const *s, char c);

// -------------------------UTILS------------------------
int	    len_tab(char **split);
int	    valid_quote(char *split);
void    free_split(char **split);
char	*remove_quotes(char *str);
char	*clean_line(char *line);
int		ft_strchr2(char *str1, char *str2);


#endif