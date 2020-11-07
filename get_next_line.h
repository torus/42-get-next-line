/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thisai <thisai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:42:13 by thisai            #+#    #+#             */
/*   Updated: 2020/11/07 16:06:22 by thisai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <stddef.h>

int	get_next_line(int fd, char **line);

typedef struct s_buffer_list t_buffer_list;

struct s_buffer_list
{
	int				fd;
	char			buffer[BUFFER_SIZE];
	size_t			cursor;
	size_t			size;
	t_buffer_list	*next;
	int				eof;
};

typedef struct s_string_list t_string_list;

struct s_string_list
{
	char		*str;
	size_t			size;
	t_string_list	*next;
};

void	*ft_memcpy(void *dst, const void *src, size_t n);


#endif
