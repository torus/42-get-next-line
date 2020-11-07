/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thisai <thisai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:25:09 by thisai            #+#    #+#             */
/*   Updated: 2020/11/07 17:47:20 by thisai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

static t_buffer_list	*find_buffer(t_buffer_list *buffers, int fd)
{
	while (buffers)
	{
		if (buffers->fd == fd)
			return buffers;
		buffers = buffers->next;
	}
	return (NULL);
}

#include <stdio.h>

int	get_next_line(int fd, char **line)
{
	static t_buffer_list	*buffers;
	t_buffer_list			*buf;

	printf("buffers: %p\n", buffers);

	buf = find_buffer(buffers, fd);
	if (!buf)
	{
		buf = malloc(sizeof(t_buffer_list));
		buf->fd = fd;
		buf->cursor = 0;
		buf->size = 0;
		buf->next = buffers;
		buf->eof = 0;
		buffers = buf;
	}

	t_string_list	*strings;
	t_string_list	*str;
	strings = NULL;
	size_t	index;
	int done;

	done = 0;
	while (!done)
	{
		if (buf->cursor == buf->size)
		{
			size_t	read_size;
			read_size = read(fd, buf->buffer, BUFFER_SIZE);
			buf->size = read_size;
			buf->cursor = 0;
			if (read_size == 0)
				break ;
			/* printf("read: \"%s\"\n", buf->buffer); */
		}

		index = buf->cursor;
		while (index < buf->size && buf->buffer[index] != '\n')
			index++;
		str = malloc(sizeof(t_string_list));
		str->next = strings;
		strings = str;
		str->size = index - buf->cursor;
		str->str = malloc(str->size);
		ft_memcpy(str->str, buf->buffer + buf->cursor, str->size);
		buf->cursor = index;

		/* printf("copied: \"%s\"\n", str->str); */

		if (buf->buffer[index] == '\n')
		{
			buf->cursor++;
			done = 1;
		}
	}

	int	len;
	len = 0;
	str = strings;
	while (str)
	{
		len += str->size;
		str = str->next;
		printf("len: %d\n", len);
	}

	char	*dest;
	char	*p;
	dest = malloc(len + 1);
	p = dest + len;
	*p = '\0';
	str = strings;
	while (str)
	{
		t_string_list	*next;
		next = str->next;
		ft_memcpy(p - str->size, str->str, str->size);
		/* printf("appending: %ld: \"%s\"\n", str->size, str->str); */
		p -= str->size;
		free(str->str);
		free(str);
		str = next;
	}

	printf("result: \"%s\"\n", dest);
	*line = dest;
	return 1;
}
