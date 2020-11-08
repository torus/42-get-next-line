#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#include "src/get_next_line.h"

void test_fd(int fd)
{
	char *line = NULL;
	int result = get_next_line(fd, &line);

	assert(result == 1);
	assert(line);

	assert(!strcmp(line, "Lorem ipsum dolor sit amet,"));
	free(line);

	result = get_next_line(fd, &line);

	assert(result == 1);
	assert(line);

	assert(!strcmp(line, "consectetur adipiscing elit,"));
	free(line);

	int count = 0;
	while(get_next_line(fd, &line) > 0)
	{
		printf("read: %s\n", line);
		count++;
	}
	assert(count == 6);
}

int main(void)
{
	test_fd(0);

	int fd = open("sample.txt", O_RDONLY);
	test_fd(fd);

	return 0;
}
