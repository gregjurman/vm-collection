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

#include <opcodes.h>
#include <inspect.h>
#include <structs.h>
#include <args.h>


// Our virtual machine
int dispatch(FILE * fp) {
    // We have 4 registers
    char registers[4] = {0};

    // Our current operation
    operation_struct op;

    // Lets keep count of how many instructions we have proccessed
    size_t op_num = 0;

    // Include our targeting macro
    #include <target_def.h>

    /* After pre-processing adds the appropriate labels to the code,
     * we define our target list in a static array for our opcodes.
     *
     * This way we can take the numerical value of our opcode 
     * (for example, OP_DISPLAY is 3) and reference it to a list rather
     * than evaluating it against a switch/case. Rather than a long chain
     * of host-machine compare(CMP on the MSP430), this allows us to jump 
     * (JMP) immeditely to the instructions that need to be run rather than 
     * spending about (opcode_value + 1) * 2 instructions to work through the
     * switch-case.
     *
     * On larger virtual machines, this means opcodes that are way at the 
     * bottom of the switch/case will begin execution at the same time.
     * It no longer matters where in the switch-case the opcode begins at,
     * they only need a single JMP to get to rather than X number of CMP+JNE
     * statements if the switch-case needed to be evaluated.
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
    struct arguments arguments;
     
    /* Default values. */
    arguments.verbose = 0;
    arguments.bit_file = NULL;
     
    /* Parse our arguments; every option seen by parse_opt will
    * be reflect`ed in arguments. */
    argp_parse (&argp, argc, argv, 0, 0, &arguments); 
    // Lets open our bytecode file
    FILE * fd = fopen(arguments.bit_file, "rb");
    if (fd == NULL) {
        printf("Cannot access file!\n");
        exit(127);
    }

    // Lets do this thing!
    dispatch(fd);

    // Close our bytecode files
    fclose(fd);
}
