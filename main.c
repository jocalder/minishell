#include "unistd.h"
#include "stdio.h"
#include <sys/types.h>
#include <sys/time.h>
#include <sys/ioctl.h>

int main(void)
{
	int fd = STDIN_FILENO;
	char *console = ttyname(fd);

	printf("%s\n", console);
	return (1);
}
