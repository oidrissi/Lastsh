/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidrissi <oidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 21:23:05 by oidrissi          #+#    #+#             */
/*   Updated: 2021/11/16 14:48:09 by oidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ft_bzero
void	ft_bzero(void *s, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = 0;
		i++;
	}
}

// ft_calloc
void	*ft_calloc(size_t count, size_t size)
{
    void	*ptr;

    ptr = malloc(count * size);
    if (!ptr)
        return (NULL);
    ft_bzero(ptr, count * size);
    return (ptr);
}

// ft_strlen
size_t	ft_strlen(const char *s)
{
    size_t	i;

    i = 0;
    while (s[i])
        i++;
    return (i);
}

char	*ft_strcat(char *dest, const char *src)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}
