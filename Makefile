#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thisai <thisai@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/07 13:03:22 by thisai            #+#    #+#              #
#    Updated: 2020/11/07 17:47:26 by thisai           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

TARGET = testmain
SRCS = $(wildcard src/*.c)
HEADERS = $(wildcard src/*.h)

# CFLAGS = -Wall -Wextra -Werror -D BUFFER_SIZE=32
CFLAGS = -Wall -Wextra -D BUFFER_SIZE=32 -fsanitize=address

test: $(TARGET)
	./$(TARGET) < sample.txt

$(TARGET): $(SRCS) $(HEADERS) main.c
	$(CC) -g -o $@ $(CFLAGS) $^
