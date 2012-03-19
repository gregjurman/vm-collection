// MSP430 VM - Virtual Machine for the MSP430 microcontroller
//
// Greg Jurman <gdj2214@rit.edu>
//

#include <stdio.h>
#include <stdlib.h>

#include <opcodes.h>
#include <structs.h>
#include <memory.h>

// Our MSP430 VM!
int dispatch(FILE * bitfile) {
    return 0;
}

// Main entry point
void main(int argc, char * argv[]) {
    // do an argument check
    if (argc < 2 || argc > 3) {
        printf("Usage: msp430 bitfile\n");
        exit(1);
    }
    
    // Lets open our bytecode file
    FILE * fd = fopen(argv[1], "rb");
    if (!fd) {
        printf("Cannot access bytecode file!\n");
        exit(127);
    }

    // Lets do this thing!
    int err_code = dispatch(fd);

    // Close our bytecode files
    if (fd) fclose(fd);

    // Print an error code if needed
    if (err_code != 0) {
        printf("VM failed with error code: %i\n", err_code);
    }

    exit(0);
}
