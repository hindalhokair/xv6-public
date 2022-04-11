#include "param.h"
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "syscall.h"
#include "traps.h"
#include "memlayout.h"
#include "types.h"
#include "mmu.h"

int
main(int argc, char *argv[])
{
    printf(1, "Read only protection test starting...\n");
    // Start address
    char *start_addr = sbrk(0);
    // Size of our allocated memory
    sbrk(2 * PGSIZE);
    printf(1, "Start address: %d\n", start_addr);
    printf(1, "Value at start address: %d\n", *start_addr);
    // Protect 2 pages starting from start_addr
    mprotect(start_addr, 2);
    // Test if protection is inherited by forks
    int fork_test = fork();

    if(fork_test == 0) // Check if first fork
    {
        printf(1, "Attempt to edit protected address...\n");
        // Change value at start address, this should be protected by inheritance
        *start_addr = 10;
        printf(1, "Code does not reach this statement because of the trap\n");
        exit();
    }
    
    else if(fork_test > 0)
    {
        wait();
        // Unprotect first page
        munprotect(start_addr, 1);
        printf(1, "Attempt to edit unprotected address in first page...\n");
        *start_addr = 10;
        printf(1, "New value at start address: %d\n", *start_addr);
        printf(1, "Check that second page is still protected...\n");
        // Try changing value at the second page
        *(start_addr + PGSIZE) = 10;
        printf(1, "Code does not reach this statement because of the trap\n");
        exit();
    }
    exit();

}