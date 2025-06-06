#include "minishell.h"

int get_random_int(void)
{
	int fd = open("/dev/urandom", O_RDONLY);
	unsigned int num = 0;

	if (fd < 0)
		return -1;
	read(fd, &num, sizeof(num));
	close(fd);
	return ((int)(num % 100));
}
