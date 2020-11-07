/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thisai <thisai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 15:25:40 by thisai            #+#    #+#             */
/*   Updated: 2020/11/07 15:52:14 by thisai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*p;

	if (src == dst)
		return (dst);
	p = dst;
	while (n--)
		*p++ = *(char*)src++;
	return (dst);
}
