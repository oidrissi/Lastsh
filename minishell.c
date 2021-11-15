/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidrissi <oidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 20:55:34 by oidrissi          #+#    #+#             */
/*   Updated: 2021/11/15 22:43:00 by oidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer *lexer(char *line)
{
	t_lexer *lex;

	lex = (t_lexer *)malloc(sizeof(t_lexer));
	lex->contents = line;
	lex->i = 0;
	lex->c = line[lex->i];

	return (lex);                           
}

void	advance_lexer(t_lexer *lexer)
{
	if (lexer->c != '\0' && lexer->i < ft_strlen(lexer->contents))
	{
		lexer->i += 1;
		lexer->c = lexer->contents[lexer->i];
	}
}

void	lexer_skip_whitespaces(t_lexer *lexer)
{
	while (lexer->c == ' ' || lexer->c == '\t')
		advance_lexer(lexer);
}

t_token	*init_token(int type, char *value)
{
	t_token *token;
	token = (t_token *)malloc(sizeof(t_token));
	token->e_type = type;
	token->value = value;
	return (token);
}

t_token	*advance_with_token(t_lexer *lexer, t_token *token)
{
	advance_lexer(lexer);
	return (token);
}

t_token	*get_next_token(t_lexer *lexer)
{
	while (lexer->c != '\0' && lexer->i < ft_strlen(lexer->contents))
	{
		if (lexer->c == ' ' || lexer->c == '\t')
			lexer_skip_whitespaces(lexer);
		if (lexer->c == '\"')
			return (collect_string(lexer));
		if (lexer->c == '>')
			return (advance_with_token(lexer, init_token(TOKEN_GREAT, get_char_as_token(lexer))));
		if (lexer->c == '<')
			return (advance_with_token(lexer, init_token(TOKEN_LESS, get_char_as_token(lexer))));
		if (lexer->c == '|')
			return (advance_with_token(lexer, init_token(TOKEN_PIPE, get_char_as_token(lexer))));
	}
	return (NULL);
}

t_token *collect_string(t_lexer *lexer)
{
	char *value;
	char *s;
	
	value = (char *)malloc(sizeof(char));
	value[0] = '\0';
	advance_lexer(lexer);
	while (lexer->c != '\"')
	{
		s = get_char_as_token(lexer);
		value = realloc(value, (ft_strlen(value) + ft_strlen(s) + 1) * sizeof(char));
		strcat(value, s);
	}
	advance_lexer(lexer);

	return (init_token(TOKEN_WORD, value));
}

char	*get_char_as_token(t_lexer *lexer)
{
	char *str = (char *)malloc(sizeof(char));
	str[0] = lexer->c;
	str[1] = '\0';

	return (str);
}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	(void)envp;
	printf("%s\n", "hello");
	return (0);
}