#include "main.h"

/**
 * start_check - function that checks value of ac
 * @ac: command-line argument
 */

void start_check(int ac)
{
	if (ac == 1)
		return;
	exit(1);
}
