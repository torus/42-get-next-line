#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "src/get_next_line.h"

int main(void)
{




	char *line = NULL;
	int result = get_next_line(0, &line);

	assert(result == 1);
	assert(line);

	assert(!strcmp(line, "Lorem ipsum dolor sit amet,"));
	free(line);

	result = get_next_line(0, &line);

	assert(result == 1);
	assert(line);

	assert(!strcmp(line, "consectetur adipiscing elit,"));
	free(line);

	return 0;
}
