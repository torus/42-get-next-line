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

int				get_next_line(int fd, char **line);

typedef struct	s_buflist
{
	int					fd;
	char				buffer[BUFFER_SIZE];
	size_t				cursor;
	size_t				size;
	struct s_buflist	*next;
	struct s_buflist	*prev;
	int					occupied;
}				t_buffer_list;

typedef struct	s_strlist
{
	char				*str;
	size_t				size;
	struct s_strlist	*next;
}				t_string_list;

t_buffer_list	*find_buffer(t_buffer_list *buffers, int fd);
t_buffer_list	*new_buffer_list(t_buffer_list *tail, int fd);
int				load_to_buffer(t_buffer_list *buf, int fd);
t_string_list	*new_string(t_string_list *tail, const char *str, size_t size);
void			clean_up_buffer(t_buffer_list *head, t_buffer_list *buf, int status);

#endif
