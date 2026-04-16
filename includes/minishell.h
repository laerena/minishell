/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leilai <leilai@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 18:12:16 by leilai            #+#    #+#             */
/*   Updated: 2026/04/16 12:51:52 by leilai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
/*
** Quotes affect how a word is read
** Not yet included here
*/

/* eg. state == 2 --> state == REJECTED */
typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_APPEND, /* >> */
	T_HEREDOC,
}	t_token_type;


typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

/* AST node type */
typedef enum e_node_type
{
	NODE_CMD,
	NODE_PIPE,
	NODE_REDIR_IN,
	NODE_REDIR_OUT,
	NODE_APPEND,
	NODE_HEREDOC
}	t_node_type;

/* AST node (treeee) */
typedef struct s_ast
{
	t_node_type		type;
	char			**av;
	char			*file;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

typedef struct s_shell
{
	char	**envp;
	int		last_exit_status; /* echo $? */
}	t_shell;

/* lexer */
t_token	*lexer_tokenize(const char *input);
void	token_clear(t_token **lst);
void	print_tokens(t_token *tokens);


#endif