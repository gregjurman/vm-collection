// Lab 1 VM - Virtual Machine for Lab 1 of 0618.303
//
// This is meant to be supplimental material for Lab 1 for people
// (myself included) to better understand the workings of a virtual machine.
//
// Greg Jurman <gdj2214@rit.edu>
//
//

#include <stdio.h>
#include <stdlib.h>

// Define our opcodes
#define OP_DISPLAY  3 //48
#define OP_WRITE    2 //32
#define OP_READ     1 //16
#define OP_COPY     0 //0


// We have 4 registers
char registers[4] = {0};

//Define our command struct
typedef struct {
    unsigned char padding : 2;
    unsigned char opcode : 2;
    unsigned char src : 2;
    unsigned char dest : 2;
} cmd_struct;

// Define our complete operation struct
typedef struct {
    cmd_struct cmd;
    unsigned char input : 4;
    unsigned char output : 4;
} operation_struct;


// Our virtual machine
int dispatch(FILE * fp) {
    operation_struct op;

#define TARGET(op) \
    TARGET_##op: \
    case op: 

    // Define targets (these let us haul ass)
    static void * op_targets[4] = {
        &&TARGET_OP_DISPLAY,
        &&TARGET_OP_WRITE,
        &&TARGET_OP_READ,
        &&TARGET_OP_COPY
    };

    // Our main VM loop
    while(fread(&op, sizeof(operation_struct), 1, fp) == 1) {
        dispatch:
        if(fread(&op, sizeof(operation_struct), 1, fp) != 1) break;

        goto *op_targets[op.cmd.opcode];

        switch(op.cmd.opcode) { // We should never have to evaluate this
            TARGET(OP_DISPLAY)
                printf("Display ");
                goto dispatch;

            TARGET(OP_WRITE)
                printf("Write ");
                goto dispatch;
    
            TARGET(OP_READ)
                printf("Read ");
                goto dispatch;

            TARGET(OP_COPY)
                printf("Copy ");
                goto dispatch;
        }
    }
    printf("Broke!\n");

    return 0;
}

// Main entry point
int main(int argc, char * argv[]) {
    // do an argument check
    if (argc != 1) {
        printf("Usage: lab1vm bitfile\n");
        exit(1);
    }
    
    // Lets open our bytecode file
    FILE * fd = fopen(argv[1], "r");
    if (fd == NULL) {
        printf("Cannot access file!\n");
        exit(127);
    }

    // TODO: Dispatch

    // Close our bytecode files
    fclose(fd);
}
