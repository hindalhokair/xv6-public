#include "types.h"
#include "user.h"
#include <stddef.h>


int
main(void)
{
    printf(1, "Starting null pointer derefrencing test...\n");
    int *x = NULL;  // x is a null pointer
    *x = 0;         // trap because of dereferencing x
    printf(1, "Code does not reach this statement because of the trap\n");
    exit();
}