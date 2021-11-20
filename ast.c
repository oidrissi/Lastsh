/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidrissi <oidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 20:13:10 by oidrissi          #+#    #+#             */
/*   Updated: 2021/11/18 00:25:30 by oidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*init_ast(int type)
{
    t_ast   *ast = malloc(sizeof(t_ast));
    ast->type = type;

    ast->function = NULL;
	ast->function_call = NULL;
	ast->function_arg_size = 0;
	ast->string_value = NULL;
    return (ast);
}
