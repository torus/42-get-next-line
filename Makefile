#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thisai <thisai@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/07 13:03:22 by thisai            #+#    #+#              #
#    Updated: 2020/11/08 18:39:43 by thisai           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

BUFFER_SIZE = 32
TARGET = testmain-$(BUFFER_SIZE)
SRCS = $(wildcard src/*.c) main.c
HEADERS = $(wildcard src/*.h)

# CFLAGS = -Wall -Wextra -Werror -D BUFFER_SIZE=32
CFLAGS = -Wall -Wextra -D BUFFER_SIZE=$(BUFFER_SIZE) -fsanitize=address

testall:
	$(MAKE) test BUFFER_SIZE=1
	$(MAKE) test BUFFER_SIZE=32
	$(MAKE) test BUFFER_SIZE=9999
	$(MAKE) test BUFFER_SIZE=10000000

test: $(TARGET)
	./$(TARGET) < sample.txt

$(TARGET): $(SRCS) $(HEADERS)
	$(CC) -o $@ $(CFLAGS) $(SRCS)
