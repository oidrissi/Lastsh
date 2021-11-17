/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidrissi <oidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 20:55:44 by oidrissi          #+#    #+#             */
/*   Updated: 2021/11/17 00:14:37 by oidrissi         ###   ########.fr       */
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



t_lexer *lexer(char *line);
size_t	ft_strlen(const char *s);
void	advanced_lexer(t_lexer *lexer);
void	lexer_skip_whitespaces(t_lexer *lexer);
t_token	*init_token(int type, char *value);
t_token	*get_next_token(t_lexer *lexer);
t_token *collect_string(t_lexer *lexer);
char	*get_char_as_token(t_lexer *lexer);
void	*ft_realloc(void *ptr, size_t size);
char	*ft_strcat(char *dest, const char *src);


#endif /* MINIHELL_H */