/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidrissi <oidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 20:55:34 by oidrissi          #+#    #+#             */
/*   Updated: 2021/11/15 22:25:52 by oidrissi         ###   ########.fr       */
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

t_token	*get_next_token(t_lexer *lexer)
{
	while (lexer->c != '\0' && lexer->i < ft_strlen(lexer->contents))
	{
		if (lexer->c == ' ' || lexer->c == '\t')
			lexer_skip_whitespaces(lexer);
		if (lexer->c == '\"')
			return (advance_with_token(lexer, init_token(TOKEN_QUOTE, get_char_as_token(lexer))));
		if (lexer->c == '>')
		{
			return (advance_with_token(lexer, init_token(TOKEN_GREAT, get_char_as_token(lexer))));
		}
		if (lexer->c == '<')
			return (advance_with_token(lexer, init_token(TOKEN_LESS, get_char_as_token(lexer))));
		if (lexer->c == '|')
			return (advance_with_token(lexer, init_token(TOKEN_PIPE, get_char_as_token(lexer))));
	}
	return (NULL);
}

t_token	*advance_with_token(t_lexer *lexer, t_token *token)
{
	advance_lexer(lexer);
	return (token);
}

t_token *collect_string(t_lexer *lexer)
{
	char *str;
	int i;
	int j;

	i = lexer->i;
	j = 0;
	str = (char *)malloc(sizeof(char) * (ft_strlen(lexer->contents) + 1));
	while (lexer->contents[i] != '\"')
	{
		str[j] = lexer->contents[i];
		i++;
		j++;
	}
	str[j] = '\0';
	lexer->i = i + 1;
	lexer->c = lexer->contents[lexer->i];
	return (init_token(TOKEN_WORD, str));
}

char	*get_char_as_token(t_lexer *lexer);

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	(void)envp;
	printf("%s\n", "hello");
	return (0);
}