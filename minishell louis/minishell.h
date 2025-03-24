/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-guil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:32:46 by lde-guil          #+#    #+#             */
/*   Updated: 2025/03/14 13:32:49 by lde-guil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <termios.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

# define DELIMITER "|<>"
# define QUOTES "\'\""
# define NORMAL 0
# define IN 1
# define OUT 2
# define OUT_APPEND 3
# define ERROR_CHAR "<>|&"

/*
TOKEN LIST :
    - ARG
    - CMD
    - BUILTIN
    - REDIR-OUT
    - REDIR-IN
    - INFILE
    - OUTFILE
*/

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
}	t_list;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
    int             builtin;
    char            *name;
    char            *path;
    char            **args;
    char            *infile;
    char            *outfile;
}   t_cmd;

typedef struct s_data
{
    t_env   **env;
    t_list  *list;
    t_cmd   *cmd;
    char    **envp;
    int     exit_status;
}   t_data;



// ________________________EXEC__________________________

// ----------------------BUILTINS------------------------
int		ft_cd(char *str);
int	    ft_echo(char **args);
int     ft_export(char *var, t_data *data);
int		ft_pwd(void);
int     ft_unset(char *varname, t_data *data);

// ------------------CREATE ENVIRONMENT------------------
t_env	**create_env(char **envp);
char	*get_var_name(char *str);
char	*get_var_value(char *str);

// ---------------------EXEC COMMAND---------------------
void    exec_list(t_data *data);
void    exec_command(t_data *data);
void    child_pr(t_data *data);

// ---------------------FIND COMMAND---------------------
int     is_builtin(t_list *list);
char    *get_path(char *cmd, t_env **env);

// -----------------------FREEING------------------------
void    ft_free_env_element(t_env *var);
void    ft_free_cmd(t_cmd *cmd);

// ----------------------INIT DATAS----------------------
t_data  *init_data(char **envp);
t_cmd   *create_cmd(t_list *list);

// ------------------------UTILS-------------------------
void	ft_free(t_env **env);
void	display_env(t_env **env);
void    ft_free_tab(char **tab);
char    *fetch_value(char *name, t_env **env);
char    *get_cmd_name(char *path);



// ______________________ PARSING________________________

// -------------------------CORE-------------------------
void	minishell(char	*line, t_list *list);
void	analyze_line(char **split, t_list *list);

// ----------------------FIND LIST-----------------------
int	    find_builtin(char *split, t_list *list, int index);
int	    find_cmd(char *split, t_list *list, int index);
int	    find_token(char *split, t_list *list, int index);
void	find_file(char *split, t_list *list, int index, int redir);
void	find_opt_arg(char *split, t_list *list, int index);

// ----------------------LIST UTILS----------------------
t_list	*initialisation(void);
void	afficherliste(t_list *liste);
void	insertion_element(t_list *liste, char *arg, char *token, int index);
void	destruction(t_list *liste);
void	insertion_list(t_list *liste);

// ----------------------- PARSING-----------------------
int		start_parse(char **split);
int		syntax_error(char **split, int len_split);
int	    parse_one_case(char *split);
char	*chr_str(char *str, char *to_find);

// -------------------------UTILS------------------------
int	    len_tab(char **split);
int	    valid_quote(char *split);
void    free_split(char **split);
char	*remove_quotes(char *str);
char	*clean_line(char *line);

#endif