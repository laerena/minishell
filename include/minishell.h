
#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef FALSE
#  define FALSE 0
# endif

# ifndef TRUE
#  define TRUE 1
# endif

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/include/libft.h"
# include "../libft/include/ft_printf.h"

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_APPEND,
	T_HEREDOC,
	T_AND,
	T_OR,
	T_LPAREN,
	T_RPAREN,
	T_UNKNOWN
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef enum e_node_type
{
	N_EXEC,
	N_PIPE,
	N_REDIR,
	N_AND,
	N_OR,
	N_SUBSHELL,
}	t_node_type;

typedef enum e_redir_type
{
	R_INPUT,
	R_OUTPUT,
	R_APPEND,
	R_HEREDOC
}	t_redir_type;

typedef struct s_cmd	t_cmd;

typedef struct s_execmd
{
	char	**argv;
	int		is_builtin;
}	t_execmd;

typedef struct s_binopcmd
{
	t_cmd	*left;
	t_cmd	*right;
}	t_binopcmd;

typedef struct s_redircmd
{
	t_cmd			*cmd;
	char			*file;
	t_redir_type	type;
}	t_redircmd;

typedef struct s_subshellcmd
{
	t_cmd		*child;
}	t_subshellcmd;

typedef struct s_cmd
{
	t_node_type	type;
	union
	{
		t_execmd		exec;
		t_binopcmd		binop;
		t_redircmd		redir;
		t_subshellcmd	subshell;
	}	u_cmd;
}	t_cmd;

typedef struct s_ctx
{
	char	**envp;
	t_cmd	*ast_head;
	int		last_exit_status;
}	t_ctx;

#endif