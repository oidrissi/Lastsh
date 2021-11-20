/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidrissi <oidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 20:55:34 by oidrissi          #+#    #+#             */
/*   Updated: 2021/11/20 07:44:20 by oidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_error_status = 0;

t_lexer *init_lexer(char *line)
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

t_token *collect_word(t_lexer *lexer)
{	
	char *value;
	char *s;
	
	value = (char *)malloc(sizeof(char));
	value[0] = '\0';
	while (isalnum(lexer->c) || lexer->c == '-' || lexer->c == '$')
	{
		s = get_char_as_token(lexer);
		value = ft_realloc(value, (ft_strlen(value) + ft_strlen(s) + 1) * sizeof(char));
		ft_strcat(value, s);
		advance_lexer(lexer);
	}
	advance_lexer(lexer);
	return (init_token(TOKEN_WORD, value));
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
		if (isalnum(lexer->c) || lexer->c == '-' || lexer->c == '$')
			return (collect_word(lexer));
		if (lexer->c == '>')
			return (advance_with_token(lexer, init_token(TOKEN_GREAT, get_char_as_token(lexer))));
		if (lexer->c == '<')
			return (advance_with_token(lexer, init_token(TOKEN_LESS, get_char_as_token(lexer))));
		if (lexer->c == '|')
			return (advance_with_token(lexer, init_token(TOKEN_PIPE, get_char_as_token(lexer))));
	}
	return ((void *)0);
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
		value = ft_realloc(value, (ft_strlen(value) + ft_strlen(s) + 1) * sizeof(char));
		ft_strcat(value, s);
		advance_lexer(lexer);
	}
	advance_lexer(lexer);
	return (init_token(TOKEN_WORD, value));
}

t_token *collect_env(t_lexer *lexer)
{
	char *value;
	char *s;
	
	value = (char *)malloc(sizeof(char));
	value[0] = '\0';
	advance_lexer(lexer);
	if (lexer->c == '$')
	{
		s = get_char_as_token(lexer);
		value = ft_realloc(value, (ft_strlen(value) + ft_strlen(s) + 1) * sizeof(char));
		ft_strcat(value, s);
		advance_lexer(lexer);
	}
	return (init_token(TOKEN_ENV, value));
}

char	*get_char_as_token(t_lexer *lexer)
{
	char *str = (char *)malloc(sizeof(char));
	if (lexer->c == '|')
	{
		advance_lexer(lexer);
		if (lexer->c == '|')
			g_error_status = 1;
	}
	str[0] = lexer->c;
	str[1] = '\0';

	return (str);
}

// if quotes are not closed, return 1
int		check_quotes(char *line)
{
	int i;
	int quotes;

	i = 0;
	quotes = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\"')
			quotes++;
		i++;
	}
	if (quotes % 2 == 1)
		return (1);
	return (0);
}

int		parse_basic_errors(char *s)
{
	if (s[0] == '|' || s[ft_strlen(s) - 1] == '|')
		return (1);
	if (check_quotes(s))
		return (1);
	return (0);
}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	(void)envp;
	char *line;
	
	char *prompt = "hell420 > ";
	t_lexer *lexer = malloc(sizeof(t_lexer));
	t_token *token = (void *)0;
	while (1)
	{
		line = readline(prompt);
		if (*line)
			add_history(line);
		if (parse_basic_errors(line))
		{
			write(1, "Error: invalid syntax\n", 23);
			continue;
		}
		lexer = init_lexer(line);
		while ((token = get_next_token(lexer)) != (void *)0)
		{
			printf("TOKEN : (%d;%s)\n", token->e_type, token->value);
		}	
	}
	return (0);
}

// if (g_error_status == 1)
// {
// 	printf("parse error\n");
// 	g_error_status = 0;
// 	break ;
// }