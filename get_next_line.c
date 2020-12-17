/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thisai <thisai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:25:09 by thisai            #+#    #+#             */
/*   Updated: 2020/12/06 15:37:06 by thisai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line.h"

static int				string_list_length(t_string_list *str)
{
	int	len;

	len = 0;
	while (str)
	{
		len += str->size;
		str = str->next;
	}
	return (len);
}

static char				*join_strings(t_string_list *str)
{
	int				len;
	char			*dest;
	char			*p;
	t_string_list	*next;

	len = string_list_length(str);
	dest = malloc(len + 1);
	if (!dest)
		return (NULL);
	p = dest + len;
	*p = '\0';
	while (str)
	{
		next = str->next;
		if (dest)
			ft_memcpy(p - str->size, str->str, str->size);
		p -= str->size;
		free(str->str);
		free(str);
		str = next;
	}
	return (dest);
}

static t_string_list	*append_string(t_string_list *strings,
											t_buffer_list *buf, int *done)
{
	size_t			index;

	*done = 0;
	index = buf->cursor;
	while (index < buf->size && buf->buffer[index] != '\n')
		index++;
	strings = new_string(strings, buf->buffer + buf->cursor,
							index - buf->cursor);
	buf->cursor = index;
	if (buf->cursor < buf->size && buf->buffer[index] == '\n')
	{
		buf->cursor++;
		*done = 1;
	}
	return (strings);
}

t_string_list			*make_string_list_from_buffer(t_buffer_list *buf,
														int fd, int *status)
{
	t_string_list	*strings;
	int				done;

	strings = NULL;
	done = 0;
	*status = 1;
	while (!done)
	{
		if (buf->cursor == buf->size)
		{
			if ((*status = load_to_buffer(buf, fd)) < 0)
				return (NULL);
			if (buf->size == 0)
			{
				if (!strings)
					return (NULL);
				break ;
			}
		}
		strings = append_string(strings, buf, &done);
	}
	return (strings);
}

int						get_next_line(int fd, char **line)
{
	static t_buffer_list	buffers;
	t_buffer_list			*buf;
	t_string_list			*strings;
	char					*dest;
	int						status;

	buf = find_buffer(&buffers, fd);
	if (!buf)
	{
		buf = new_buffer_list(buffers.next, fd);
		if (!buf)
			return (-1);
		buffers.next = buf;
	}
	strings = make_string_list_from_buffer(buf, fd, &status);
	if (status >= 0) {
		dest = join_strings(strings);
		*line = dest;
		if (!dest)
			status = -1;
	}
	return (status > 0 ? 1 : status);
}
