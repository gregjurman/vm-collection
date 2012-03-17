// MU0 VM - Virtual Machine for the MU0 simple microcontroller
// from Imperial College London.
//
// More Info: http://cas.ee.ic.ac.uk/people/gac1/Architecture/Lecture2.pdf
//
// Greg Jurman <gdj2214@rit.edu>
//
//

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Define our opcodes
#define OP_LDA 0 // ACC := mem[S]
#define OP_STO 1 // mem[S] := ACC
#define OP_ADD 2 // ACC := ACC + mem[S]
#define OP_SUB 3 // ACC := ACC - mem[S]
#define OP_JMP 4 // PC := S
#define OP_JGE 5 // if ACC > 0, PC := S
#define OP_JNE 6 // if ACC != 0, PC := S
#define OP_STP 7 // stop
#define OP_INVALID -1; // Invalid OP_Code

// Define our registers
#define REG_PC 0
#define REG_ACC 1
#define REG_IR 2


// Define how the opcodes look in bit-fields
typedef struct {
    uint16_t s : 12;
    uint16_t opcode : 4;
} operation_struct;

// Our MU0 VM!
int dispatch(FILE * fp) {
    int error_code = 0;
    uint16_t * heap;
    void * code;

    // Make a heap
    heap = malloc(sizeof(uint16_t) * 4096);
    if (heap == NULL) {
        printf("VM Error: Cannot allocate heap!");
        fp = NULL;
        error_code = -1;
    }

    // Size up our code-space and read in our code
    if (fp != NULL) {
        // Get the size of the code-file
        fseek(fp, 0L, SEEK_END);
        size_t sz = ftell(fp);
        fseek(fp, 0L, SEEK_SET);

        // Malloc a code space
        code = malloc(sizeof(char) * sz);
        if (code == NULL) {
            printf("VM Error: Cannot allocate code memory!");
            fp = NULL;
            error_code = -3;
        }

        // Read in our code file
        if (fread(code, sizeof(char), sz, fp) != sz) return -2;
    }

    // Lets run code
    if (fp != NULL) {
        // Ok lets setup our initial registers
        uint16_t registers[3] = {0};

        // Include our targeting macro
        #include <target_def.h>

        // Our opcode target table
        void *op_targets[16] = {
            &&TARGET_OP_LDA,
            &&TARGET_OP_STO,
            &&TARGET_OP_ADD,
            &&TARGET_OP_SUB,
            &&TARGET_OP_JMP,
            &&TARGET_OP_JGE,
            &&TARGET_OP_JNE,
            &&TARGET_OP_STP,
            &&TARGET_OP_INVALID,
            &&TARGET_OP_INVALID,
            &&TARGET_OP_INVALID,
            &&TARGET_OP_INVALID,
            &&TARGET_OP_INVALID,
            &&TARGET_OP_INVALID,
            &&TARGET_OP_INVALID,
            &&TARGET_OP_INVALID
        };

        // Our main VM loop
        while(1) {
            DISPATCH:
            // Fetch the current instruction
            registers[REG_IR] = ((uint16_t *)code)[registers[REG_PC]];
            operation_struct* op = (operation_struct *)(&registers[REG_IR]);

            // Little inspection
            printf("PC: %i op: %#X, s: %#X ", 
                registers[REG_PC], 
                (*op).opcode, (*op).s);

            // Point PC to the next instruction
            registers[REG_PC]++;

            // This is where the magic happens
            goto *op_targets[(*op).opcode];

            // We will never evaluate this time consuming switch
            // because of computed-goto awesome
            switch((*op).opcode) {
                TARGET(OP_LDA) // ACC := mem[S]
                printf("LDA\n");
                registers[REG_ACC] = heap[(*op).s];
                goto DISPATCH;

                TARGET(OP_STO) // mem[S] := ACC
                heap[(*op).s] = registers[REG_ACC];
                printf("STO\n");
                goto DISPATCH;

                TARGET(OP_ADD) // ACC := ACC + mem[S]
                printf("ADD\n");
                registers[REG_ACC] += heap[(*op).s];
                goto DISPATCH;

                TARGET(OP_SUB) // ACC := ACC - mem[S]
                registers[REG_ACC] -= heap[(*op).s];
                printf("SUB\n");
                goto DISPATCH;

                TARGET(OP_JMP) // Unconditional jump, PC := S
                registers[REG_PC] = (*op).s;
                printf("JMP\n");
                goto DISPATCH;

                TARGET(OP_JGE) // if ACC > 0, PC := S
                printf("JGE\n");
                if (registers[REG_ACC] > 0) {
                    registers[REG_PC] = (*op).s;
                }
                goto DISPATCH;

                TARGET(OP_JNE) // if ACC != 0, PC := S
                printf("JNE\n");
                if (registers[REG_ACC] != 0) {
                    registers[REG_PC] = (*op).s;
                }
                goto DISPATCH;

            }

            TARGET_OP_INVALID: // Invalid Opcode
            printf("INVALID\n");
            error_code = -4;
            break;

            TARGET_OP_STP:
            printf("STP\n");
            error_code = 0;
            break;
        }
    }

    if (code != NULL) free(code);
    if (heap != NULL) free(heap);

    return error_code;
}

// Main entry point
int main(int argc, char * argv[]) {
    // do an argument check
    if (argc != 2) {
        printf("Usage: lab1vm bitfile\n");
        exit(1);
    }
    
    // Lets open our bytecode file
    FILE * fd = fopen(argv[1], "rb");
    if (fd == NULL) {
        printf("Cannot access file!\n");
        exit(127);
    }

    // Lets do this thing!
    int err_code = dispatch(fd);
    if (err_code != 0) {
        printf("VM failed with error code: %i\n", err_code);
    }

    // Close our bytecode files
    fclose(fd);
}
