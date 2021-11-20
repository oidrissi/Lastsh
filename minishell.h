/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidrissi <oidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 20:55:44 by oidrissi          #+#    #+#             */
/*   Updated: 2021/11/20 07:45:35 by oidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct	s_env
{
    char		*name;
    char		*value;
    struct s_env	*next;
}				t_env;

typedef struct	s_cmd
{
	char		*name;
	char		**args;
	char		red;
	struct s_cmd	*next;
}				t_cmd;

typedef struct	s_token
{
	enum
	{
		TOKEN_WORD,
		TOKEN_ENV,
		TOKEN_REDIRECT,
		TOKEN_PIPE,
		TOKEN_LESS,
		TOKEN_GREAT,
		TOKEN_DLESS,
		TOKEN_DGREAT,
		TOKEN_EOF,
		TOKEN_QUOTE,
	}			e_type;
	char		*value;
}				t_token;

typedef struct s_lexer
{
	char			c;
	unsigned int	i;
	char 			*contents;
} t_lexer;


typedef struct	s_ast
{
	enum
	{
		AST_STRING,
		AST_FUNCTION,
	}				e_type;
	char			*function;
	struct s_ast	**function_call;
	size_t			function_arg_size;
	char			*string_value;
}				t_ast;

typedef struct	s_parser
{
	t_lexer *lexer;
	t_token *cur_tok;
}	t_parser;

t_lexer *lexer(char *line);
size_t	ft_strlen(const char *s);
void	advance_lexer(t_lexer *lexer);
void	lexer_skip_whitespaces(t_lexer *lexer);
t_token	*init_token(int type, char *value);
t_token	*get_next_token(t_lexer *lexer);
t_token *collect_string(t_lexer *lexer);
char	*get_char_as_token(t_lexer *lexer);
void	*ft_realloc(void *ptr, size_t size);
char	*ft_strcat(char *dest, const char *src);
t_parser *init_parser(t_lexer *lexer);
void	*parse_treat(t_lexer *lexer, int token_type);
void	*parser_parse(t_parser *parser);
t_ast	*init_ast(int type);




#endif /* MINIHELL_H */