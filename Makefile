#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thisai <thisai@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/07 13:03:22 by thisai            #+#    #+#              #
#    Updated: 2020/12/02 19:16:36 by thisai           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

BUFFER_SIZE = 32
TARGET = testmain-$(BUFFER_SIZE)
TARGET_BONUS = testmain-bonus-$(BUFFER_SIZE)
SRCS = src/get_next_line.c src/get_next_line_utils.c main.c
SRCS_BONUS = src/get_next_line_bonus.c src/get_next_line_utils_bonus.c	\
	 main.c
HEADERS = src/get_next_line.h
HEADERS_BONUS = src/get_next_line_bonus.h

# CFLAGS = -Wall -Wextra -Werror -D BUFFER_SIZE=32
CFLAGS = -Wall -Wextra -D BUFFER_SIZE=$(BUFFER_SIZE) -fsanitize=address

testall:
	$(MAKE) test BUFFER_SIZE=1
	$(MAKE) test BUFFER_SIZE=32
	$(MAKE) test BUFFER_SIZE=9999
	$(MAKE) test BUFFER_SIZE=10000000
	$(MAKE) test-bonus BUFFER_SIZE=1
	$(MAKE) test-bonus BUFFER_SIZE=32
	$(MAKE) test-bonus BUFFER_SIZE=9999
	$(MAKE) test-bonus BUFFER_SIZE=10000000

test: $(TARGET)
	./$(TARGET) < sample.txt

test-bonus: $(TARGET_BONUS)
	./$(TARGET_BONUS) < sample.txt

$(TARGET): $(SRCS) $(HEADERS)
	$(CC) -o $@ $(CFLAGS) $(SRCS)

$(TARGET_BONUS): $(SRCS_BONUS) $(HEADERS)
	$(CC) -o $@ $(CFLAGS) $(SRCS_BONUS)
