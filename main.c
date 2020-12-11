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
	int ret;
	while((ret = get_next_line(fd, &line)) >= 0)
	{
		printf("read: %d: %s\n", ret, line);
		count++;
		free(line);
		line = NULL;
		if (!ret)
			break;
	}
	printf("ret: %d\n", ret);
	assert(count == 8);
}

void test_stdin()
{
	test_fd(0);
}

void test_single_file()
{
	int fd = open("sample.txt", O_RDONLY);
	test_fd(fd);
}

void test_single_file2()
{
	//int fd = open("64.txt", O_RDONLY);
	int fd = open("Get_Next_Line_Tester/test/64bit_paragraph.txt", O_RDONLY);
	char *line;
	int count = 0;
	int ret;
	while((ret = get_next_line(fd, &line)) >= 0)
	{
		printf("read: %d: %s\n", ret, line);
		count++;
		free(line);
		line = NULL;
		if (!ret)
			break;
	}
	printf("ret: %d\n", ret);
}

void test_multiple()
{
	int fd_even = open("sample-even.txt", O_RDONLY);
	int fd_odd = open("sample-odd.txt", O_RDONLY);
	char *line1;
	char *line2;
	int res1, res2;

	do {
		res1 = get_next_line(fd_even, &line1);
		res2 = get_next_line(fd_odd, &line2);
		if (res1 >= 0)
		{
			printf("even: %s\n", line1);
			free(line1);
			line1 = NULL;
		}
		if (res2 >= 0)
		{
			printf("odd: %s\n", line2);
			free(line2);
			line2 = NULL;
		}
	} while (res1 > 0 || res2 > 0);
}

void test_invaild_fd()
{
	char *line;
	assert(get_next_line(999, &line) == -1);
}

int main(void)
{
	test_stdin();
	test_single_file();
	test_multiple();
	test_invaild_fd();
	test_single_file2();

	return 0;
}