#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thisai <thisai@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/07 13:03:22 by thisai            #+#    #+#              #
#    Updated: 2020/12/06 15:41:14 by thisai           ###   ########.fr        #
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

UNAME = $(shell uname)

# CFLAGS = -Wall -Wextra -Werror -D BUFFER_SIZE=32
# CFLAGS = -Wall -Wextra -D BUFFER_SIZE=$(BUFFER_SIZE) -fsanitize=address
CFLAGS = -Wall -Wextra -D BUFFER_SIZE=$(BUFFER_SIZE)

testall:
	$(MAKE) test BUFFER_SIZE=1
	$(MAKE) test BUFFER_SIZE=32
	$(MAKE) test BUFFER_SIZE=65
	$(MAKE) test BUFFER_SIZE=9999
	$(MAKE) test BUFFER_SIZE=10000000
	$(MAKE) test-bonus BUFFER_SIZE=1
	$(MAKE) test-bonus BUFFER_SIZE=32
	$(MAKE) test-bonus BUFFER_SIZE=65
	$(MAKE) test-bonus BUFFER_SIZE=9999
	$(MAKE) test-bonus BUFFER_SIZE=10000000

test: $(TARGET)
ifeq ($(UNAME), Linux)
	valgrind --leak-check=full --error-exitcode=666 ./$(TARGET) < sample.txt
else
	./$(TARGET) < sample.txt
endif

test-bonus: $(TARGET_BONUS)
ifeq ($(UNAME), Linux)
	valgrind --leak-check=full --error-exitcode=666 ./$(TARGET_BONUS) < sample.txt
else
	./$(TARGET_BONUS) < sample.txt
endif

$(TARGET): $(SRCS) $(HEADERS)
	$(CC) -o $@ $(CFLAGS) $(SRCS)

$(TARGET_BONUS): $(SRCS_BONUS) $(HEADERS)
	$(CC) -o $@ $(CFLAGS) $(SRCS_BONUS)
