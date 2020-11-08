/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thisai <thisai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:25:09 by thisai            #+#    #+#             */
/*   Updated: 2020/11/08 13:53:18 by thisai           ###   ########.fr       */
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

static t_buffer_list	*new_buffer_list(t_buffer_list *tail, int fd)
{
	t_buffer_list	*buf;

	buf = malloc(sizeof(t_buffer_list));
	buf->fd = fd;
	buf->cursor = 0;
	buf->size = 0;
	buf->next = tail;
	buf->eof = 0;
	return (buf);
}

static int	load_to_buffer(t_buffer_list *buf, int fd)
{
	size_t	read_size;

	read_size = read(fd, buf->buffer, BUFFER_SIZE);
	buf->size = read_size;
	buf->cursor = 0;
	return (1);
}

static t_string_list	*new_string(t_string_list *tail, const char *str, size_t size)
{
	t_string_list	*new_str;

	new_str = malloc(sizeof(t_string_list));
	new_str->next = tail;
	new_str->size = size;
	new_str->str = malloc(size);
	ft_memcpy(new_str->str, str, size);
	return (new_str);
}

#include <stdio.h>

static int			string_list_length(t_string_list *str)
{
	int	len;

	printf("strings: %p\n", str);
	len = 0;
	while (str)
	{
		len += str->size;
		str = str->next;
		printf("len: %d\n", len);
	}
	return (len);
}

static char			*join_strings(t_string_list *str)
{
	int	len;
	len = string_list_length(str);

	char	*dest;
	char	*p;
	dest = malloc(len + 1);
	p = dest + len;
	*p = '\0';
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
	return (dest);
}

t_string_list	*make_string_list_from_buffer(t_buffer_list *buf, int fd)
{
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
			load_to_buffer(buf, fd);
			if (buf->size == 0)
			{
				if (!strings)
					return (0);
				else
					break ;
			}
			/* printf("read: \"%s\"\n", buf->buffer); */
		}

		index = buf->cursor;
		while (index < buf->size && buf->buffer[index] != '\n')
			index++;
		strings = str = new_string(strings, buf->buffer + buf->cursor, index - buf->cursor);
		buf->cursor = index;

		/* printf("copied: \"%s\"\n", str->str); */

		if (buf->buffer[index] == '\n')
		{
			buf->cursor++;
			done = 1;
		}
	}
	return (strings);
}

int	get_next_line(int fd, char **line)
{
	static t_buffer_list	*buffers;
	t_buffer_list			*buf;

	printf("buffers: %p\n", buffers);

	buf = find_buffer(buffers, fd);
	if (!buf)
		buf = buffers = new_buffer_list(buffers, fd);

	t_string_list	*strings;
	strings = make_string_list_from_buffer(buf, fd);

	char	*dest;
	dest = join_strings(strings);

	printf("result: \"%s\"\n", dest);
	*line = dest;
	return 1;
}
