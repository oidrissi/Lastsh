/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidrissi <oidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 20:21:50 by oidrissi          #+#    #+#             */
/*   Updated: 2021/11/19 20:10:54 by oidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parser *init_parser(t_lexer *lexer)
{
    t_parser *parser;

    parser = malloc(sizeof(t_parser));
    parser->lexer = lexer;
    parser->current_token = NULL;
}

void	*parse_treat(t_lexer *lexer, int token_type)
{
    if (token_type == parser->cur_tok->e_type)
    {
        parser->current_token = parser->current_token->next;
        return (lexer->cur_tok->value);
    }
    else
        return (NULL);
}

void	*parser_parse(t_parser *parser)
{

}