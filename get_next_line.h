/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thisai <thisai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:42:13 by thisai            #+#    #+#             */
/*   Updated: 2020/11/08 16:05:34 by thisai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>

int							get_next_line(int fd, char **line);

typedef struct s_buflist	t_buffer_list;
struct						s_buflist
{
	int				fd;
	char			buffer[BUFFER_SIZE];
	size_t			cursor;
	size_t			size;
	t_buffer_list	*next;
	t_buffer_list	*prev;
	int				occupied;
};

typedef struct s_strlist	t_string_list;
struct						s_strlist
{
	char			*str;
	size_t			size;
	t_string_list	*next;
};

void						*ft_memcpy(void *dst, const void *src, size_t n);

t_buffer_list				*find_buffer(t_buffer_list *buffers, int fd);
t_buffer_list				*new_buffer_list(t_buffer_list *tail, int fd);
int							load_to_buffer(t_buffer_list *buf, int fd);
t_string_list				*new_string(t_string_list *tail,
										const char *str, size_t size);

#endif
