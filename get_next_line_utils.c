/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thisai <thisai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 15:25:40 by thisai            #+#    #+#             */
/*   Updated: 2020/11/08 18:09:12 by thisai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

void			*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*p;

	if (src == dst)
		return (dst);
	p = dst;
	while (n--)
		*p++ = *(char*)src++;
	return (dst);
}

t_buffer_list	*find_buffer(t_buffer_list *buffers, int fd)
{
	t_buffer_list	*buf;

	buf = buffers;
	while (buf)
	{
		if (buf->fd == fd)
			return (buf);
		buf = buf->next;
	}
	buf = buffers;
	while (buf)
	{
		if (!buf->occupied)
		{
			buf->occupied = 1;
			buf->fd = fd;
			return (buf);
		}
		buf = buf->next;
	}
	return (NULL);
}

t_buffer_list	*new_buffer_list(t_buffer_list *tail, int fd)
{
	t_buffer_list	*buf;

	buf = malloc(sizeof(t_buffer_list));
	if (!buf)
		return (NULL);
	buf->fd = fd;
	buf->cursor = 0;
	buf->size = 0;
	buf->next = tail;
	buf->occupied = 1;
	return (buf);
}

int				load_to_buffer(t_buffer_list *buf, int fd)
{
	int	read_size;

	read_size = read(fd, buf->buffer, BUFFER_SIZE);
	if (read_size >= 0)
	{
		buf->size = read_size;
		buf->cursor = 0;
	}
	return (read_size);
}

t_string_list	*new_string(t_string_list *tail,
								const char *str, size_t size)
{
	t_string_list	*new_str;

	new_str = malloc(sizeof(t_string_list));
	if (!new_str)
		return (NULL);
	new_str->next = tail;
	new_str->size = size;
	new_str->str = malloc(size);
	if (!new_str->str)
	{
		free(new_str);
		return (NULL);
	}
	ft_memcpy(new_str->str, str, size);
	return (new_str);
}
