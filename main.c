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
    unsigned char dest : 2;
    unsigned char src : 2;
    unsigned char opcode : 2;
    unsigned char padding : 2;
} cmd_struct;

void inspect_cmd_struct(cmd_struct c) {
    printf("\t%X opcode: %i, src: %i, dest: %i", 
        c, c.opcode, c.src, c.dest);
}

// Data structure
typedef struct {
    unsigned char input : 4;
    unsigned char output : 4;
} data_struct;

void inspect_data_struct(data_struct d) {
    printf("\t%X input: %i, output: %i",
        d, d.input, d.output);
}


// Define our complete operation struct
typedef struct {
    cmd_struct cmd;
    data_struct data;
} operation_struct;



// Our virtual machine
int dispatch(FILE * fp) {
    operation_struct op;
    size_t op_num = 0;
#define TARGET(op) \
    TARGET_##op: \
    case op: 

    // Define targets (these let us haul ass)
    static void * op_targets[4] = {
        &&TARGET_OP_COPY,
        &&TARGET_OP_READ,
        &&TARGET_OP_WRITE,
        &&TARGET_OP_DISPLAY,
    };

    // Our main VM loop
    while(fp != NULL) {
        dispatch:
        op_num++;

        printf("\nDispatching operation number: %li\n", op_num);

        if(fread(&op, sizeof(operation_struct), 1, fp) != 1) break;

        inspect_cmd_struct(op.cmd);
        inspect_data_struct(op.data);

        goto *op_targets[op.cmd.opcode];

        switch(op.cmd.opcode) { // We should never have to evaluate this
            TARGET(OP_DISPLAY)
                printf("\tDisplay");
                goto dispatch;

            TARGET(OP_WRITE)
                printf("\tWrite");
                goto dispatch;
    
            TARGET(OP_READ)
                printf("\tRead");
                goto dispatch;

            TARGET(OP_COPY)
                printf("\tCopy");
                goto dispatch;
        }
    }
    printf("Broke!\n");

    return 0;
}

// Main entry point
int main(int argc, char * argv[]) {
    // do an argument check
    if (argc != 2) {
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
    dispatch(fd);

    // Close our bytecode files
    fclose(fd);
}
