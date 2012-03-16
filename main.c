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
#define OP_DISPLAY  3
#define OP_WRITE    2
#define OP_READ     1
#define OP_COPY     0



void inspect_registers(char registers[]) {
    // Being lazy and not bothering looping
    printf("\tCurrent registers: %i %i %i %i\n", 
        registers[0], registers[1],
        registers[2], registers[3]);
}


//Define our command struct
typedef struct {
    unsigned char dest : 2;
    unsigned char src : 2;
    unsigned char opcode : 2;
    unsigned char padding : 2;
} cmd_struct;

void inspect_cmd_struct(cmd_struct c) {
    printf("\topcode: %i, src: %i, dest: %i\n", 
        c.opcode, c.src, c.dest);
}


// Data structure
typedef struct {
    unsigned char input : 4;
    unsigned char output : 4; //We never use these
} data_struct;

void inspect_data_struct(data_struct d) {
    printf("\tinput: %i, output: %i\n",
        d.input, d.output);
}


// Define our complete operation struct
typedef struct {
    cmd_struct cmd;
    data_struct data;
} operation_struct;



// Our virtual machine
int dispatch(FILE * fp) {
    // We have 4 registers
    char registers[4] = {0};

    // Our current operation
    operation_struct op;

    // Lets keep count of how many instructions we have proccessed
    size_t op_num = 0; 

    /* This defines how GCC contructs our switch statement
     * 
     * When you wrap one of our opcodes with TARGET() GCC will fill in the
     * blanks with the definition below.
     *
     * Example:
     *
     * `TARGET(OP_DISPLAY)` will become:
     * 
     * `TARGET_OP_DISPLAY:
     *  case OP_DISPLAY:`
     *
     * This is why we do not add a case statement or : after TARGET() as it
     * becomes filled in for us before the compiler does it's thing 
     * (hence being a pre-processor command).
     *
     * Example:
     *
     * `TARGET(OP_DISPLAY)
     *  printf("%i", op.data.input);
     *  break;`
     *
     * becomes:
     *
     * `TARGET_OP_DISPLAY:
     *  case OP_DISPLAY:
     *  printf("%i", op.data.input);
     *  break;`
    **/

    #define TARGET(op) \
        TARGET_##op: \
        case op: 

    /* After pre-processing adds the appropriate labels to the code
     * we define our target list in a static array for our opcodes.
     *
     * This way we can take the numerical value of our opcode 
     * (for example, OP_DISPLAY is 3) and reference it to a list rather
     * than evaluating it against a switch/case.
    **/

    static void * op_targets[4] = {
        &&TARGET_OP_COPY,
        &&TARGET_OP_READ,
        &&TARGET_OP_WRITE,
        &&TARGET_OP_DISPLAY,
    };

    // Our main VM loop
    while(fp != NULL) {
        DISPATCH:
        op_num++;

        printf("\n\nDispatching operation number: %li\n", op_num);
        inspect_registers(registers);

        // Read in a new 2-byte command, if not break
        if(fread(&op, sizeof(operation_struct), 1, fp) != 1) break;

        // Little bit of inspection
        inspect_cmd_struct(op.cmd);
        inspect_data_struct(op.data);

        // This is where the magic happens
        goto *op_targets[op.cmd.opcode];

        // We will never evaluate this time consuming switch
        // because of computed-goto awesome
        switch(op.cmd.opcode) {
            TARGET(OP_DISPLAY) // Pass-through
                printf("%i ", op.data.input);
                goto DISPATCH;

            TARGET(OP_WRITE) // Write to register
                registers[op.cmd.dest] = op.data.input;
                goto DISPATCH;
    
            TARGET(OP_READ) // Read(print) from register
                printf("%i ", registers[op.cmd.src]);
                goto DISPATCH;

            TARGET(OP_COPY) // Copy from source to destination register
                registers[op.cmd.dest] = registers[op.cmd.src];
                goto DISPATCH;
        }
    }

    // We have exited the loop
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

    // Lets do this thing!
    dispatch(fd);

    // Close our bytecode files
    fclose(fd);
}
