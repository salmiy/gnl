#define BUFFER_SIZE 1
#include "get_next_line.h"
#include <stdio.h>

int main()
{
	char *s = get_next_line(3);
	printf("%s", s);
	return 0;
}
