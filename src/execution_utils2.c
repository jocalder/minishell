#include "minishell.h"

void    wait_all(void)
{
    int status;

    status = 0;
    while (wait(&status) > 0)
        ;
}