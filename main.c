#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#include "src/get_next_line.h"

const char *sample_lines[] = {
	"Lorem ipsum dolor sit amet,",
	"consectetur adipiscing elit,",
	"sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.",
	"",
	"Ut enim ad minim veniam,",
	"quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.",
	"Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur.",
	"Excepteur sint occaecat cupidatat non proident,",
	"sunt in culpa qui officia deserunt mollit anim id est laborum.",
	"END OF FILE",
};

void test_loremipsum_fd(int fd)
{
	char *line = NULL;
	int result = get_next_line(fd, &line);

	assert(result == 1);
	assert(line);

	assert(!strcmp(line, sample_lines[0]));
	free(line);

	result = get_next_line(fd, &line);

	assert(result == 1);
	assert(line);

	assert(!strcmp(line, sample_lines[1]));
	free(line);

	int count = 2;
	int ret;
	while((ret = get_next_line(fd, &line)) >= 0)
	{
		assert(!strcmp(line, sample_lines[count]));
		count++;
		free(line);
		line = NULL;
		if (!ret)
			break;
	}
	assert(count == 10);
}

void test_stdin()
{
	test_loremipsum_fd(0);
}

void test_single_file()
{
	int fd = open("sample.txt", O_RDONLY);
	test_loremipsum_fd(fd);
}

void test_single_file2()
{
	int fd = open("64.txt", O_RDONLY);
	char *line;
	int count = 0;
	int ret;
	while((ret = get_next_line(fd, &line)) >= 0)
	{
		assert(strlen(line) == 64);
		count++;
		free(line);
		line = NULL;
		if (!ret)
			break;
	}
	assert(ret == 0);
}

void test_single_file3()
{
	int fd = open("64bit_paragraph.txt", O_RDONLY);
	char *line;
	int count = 0;
	int ret;
	while((ret = get_next_line(fd, &line)) >= 0)
	{
		assert(strlen(line) == 64);
		count++;
		free(line);
		line = NULL;
		if (!ret)
			break;
	}
	assert(ret == 0);
}

void test_multiple()
{
	int fd_even = open("sample-even.txt", O_RDONLY);
	int fd_odd = open("sample-odd.txt", O_RDONLY);
	char *line1;
	char *line2;
	int res1, res2;
	int count = 0;
	char buf[10];

	do {
		res1 = get_next_line(fd_even, &line1);
		res2 = get_next_line(fd_odd, &line2);

		assert(res1 >= 0);
		if (count <= 8)
		{
			sprintf(buf, "%d", count);
			assert(!strcmp(buf, line1));
		}
		free(line1);
		line1 = NULL;
		count++;

		assert(res2 >= 0);
		if (count <= 15)
		{
			sprintf(buf, "%d", count);
			assert(!strcmp(buf, line2));
		}
		free(line2);
		line2 = NULL;
		count++;
	} while (res1 > 0 || res2 > 0);
	assert(count == 18);
}

void test_invaild_fd()
{
	char *line;
	assert(get_next_line(999, &line) == -1);
}

void test_incomplete()
{
	int fd = open("sample.txt", O_RDONLY);
	char *line;
	get_next_line(fd, &line);
	free(line);
	get_next_line(fd, &line);
	free(line);
}

void test_multiple_one_by_one()
{
	int fd1 = open("sample.txt", O_RDONLY);
	int fd2 = open("sample-even.txt", O_RDONLY);
	int fd3 = open("sample-odd.txt", O_RDONLY);
	char *line;

	while (get_next_line(fd1, &line) > 0)
		free(line);
	free(line);

	while (get_next_line(fd2, &line) > 0)
		free(line);
	free(line);

	while (get_next_line(fd3, &line) > 0)
		free(line);
	free(line);
}

#define TEST(name)								\
	if (argc == 2 && !strcmp(argv[1], #name))	\
		test_ ## name()

int main(int argc, char **argv)
{
	TEST(stdin);
	TEST(invaild_fd);
	TEST(single_file);
	TEST(single_file2);
	TEST(single_file3);
	TEST(incomplete);
	TEST(multiple_one_by_one);

	// BONUS
	TEST(multiple);

	return 0;
}

#ifdef __APPLE__
#include <sys/types.h>
#include <unistd.h>

__attribute__((destructor))
void end()
{
	char buf[100];
	sprintf(buf, "leaks %d", getpid());
	printf("checking leaks with: %s\n", buf);
    system(buf);
}
#endif
