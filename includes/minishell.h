/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/07/02 19:24:01 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* Libs */
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <sys/wait.h>
# include "libft.h"

/* Macros */
# define ECHO_BUILTIN	"echo"
# define CD_BUILTIN		"cd"
# define PWD_BUILTIN	"pwd"
# define EXPORT_BUILTIN	"export"
# define UNSET_BUILTIN	"unset"
# define ENV_BUILTIN	"env"
# define EXIT_BUILTIN	"exit"

# define STDIN_FILENO 0
# define STDOUT_FILENO 1
# define STDERR_FILENO 2

/* Structs */
struct	s_cmds;
struct	s_command;
struct	s_cmd_node;

typedef struct s_tk_node
{
	char				token[100];
	char				tk_type[100];
	struct s_tk_node	*next;
}	t_tk_node;

/* Each Command */
typedef struct s_command
{
	char	*name;
	int		(*execute)(struct s_cmds *);
}	t_command;

typedef struct s_cmd_node
{
	char				*phrase;
	char				*phrase_temp;
	char				**phrase_parsed;
	char				*cmd_name;
	char				*full_args;
	char				**split_args;
	t_command			*cmd_builtin;
	char				*type;
	pid_t				pid;
	int					fd[2];
	struct s_cmd_node	*next;
	struct s_cmd_node	*prev;
}	t_cmd_node;

typedef struct s_exit_code
{
	int		code;
	char	*msg;
	char	*last_cmd;
}	t_exit_code;

/* Read Keyboard command and arguments */
typedef struct s_input
{
	char		data[256];
	char		*datacpy;
	char		*cmd_name;
	char		*cmd_args;
	char		**phrase;
}	t_input;

typedef struct s_envs
{
	char	*name;
	char	*value;
}	t_envs;

typedef struct s_path
{
	char	**path;
	int		i;
	char	*path_complete;
	int		return_access;
	char	*name;
}	t_path;

/* Array of commands */
typedef struct s_cmds
{
	t_input		*input;
	t_command	*cmd_finded;
	size_t		num_cmds;
	t_command	*arr_cmds;
	t_path		*path;
	t_exit_code	exit_code;
	char		**lexical;
	char		**envs;
	t_cmd_node	*cmd_list;
	t_cmd_node	*current;
	int			cmds_list_count;
	int			exit;
	int			signal_exit;
	int			redirects_count;
	int			signal;
	int			new;
	void		(*signal_handler)(int);
}	t_cmds;

/* Commands */
void		find_command(t_cmds *cmds);
int			count_nodes(t_cmds *cmds);
void		exec_builtin(t_cmds *cmds);
void		run_node(t_cmds *cmds);
void		load_commands(t_cmds *cmds);

/* Types Commands */
void		exec_builtin(t_cmds *cmds);
void		exec_external(t_cmds *cmds);
int			check_type_command(t_cmds *cmds);

/* Path */
char		*check_path(t_cmd_node *node);
char		*get_fullpath(t_cmds *cmds);
void		free_split(char **split_array);

/* Builtins */
int			echo_adapter(t_cmds *cmds);
int			cd_adapter(t_cmds *cmds);
int			env_adapter(t_cmds *cmds);
int			unset_adapter(t_cmds *cmds);
int			pwd_adapter(t_cmds *cmds);
int			exit_adapter(t_cmds *cmds);
int			export_adapter(t_cmds *cmds);
void		execute_cmd(t_cmds *cmds);
void		set_commands(t_cmds *cmds);
void		free_commands(t_cmds *cmds);

/* Commands */
void		init_interpreter(t_cmds *cmds);

/* Command Echo echo_utils.c */
void		echo_print_envs(char *word);
char		*echo_extract_word(char *word);
int			echo_exec_print(t_cmds *cmds, int settings, char **words);

/* Pipes */
void		open_pipe(t_cmd_node *current);

/* Redirects */
void		check_exist_redirect(t_cmds *cmds);

/* Set envs */
void		set_envs(char **envp, t_cmds *cmds);
int			count_envp(char **envp);
int			append_envs(t_cmds *cmds, char *name, char *value);
void		free_envs(t_cmds *cmds);

/* Syntax Analysis */
void		syntax_analysis(t_cmds *cmds);
void		build_struct_to_exec(t_cmds *cmds, t_tk_node *list_tokens);
void		free_cmd_nodes(t_cmd_node *list_cmds);

/* Token Analysis */
int			token_analysis(t_cmds *cmds);

/* Read Keyboard */
int			read_keyboard(t_cmds *cmds);
char		*check_data_input(t_cmds *cmds);
int			is_empty_data(t_cmds *cmds);

typedef struct s_signal_handler_data
{
	t_cmds	*cmds;
}	t_signal_handler_data;

/* Signals (signals.c) */
void		handler(int signal_num);
void		signal_handler(int signal_num);
void		signals_handlers(t_cmds *cmds);

/* Minishell Utils */
int			interactive_exit(t_cmds *cmds);
void		free_arr(char **arr);

/* Minishell  main.c */
int			minishell(t_cmds *cmds);
#endif