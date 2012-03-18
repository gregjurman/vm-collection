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

#include <opcodes.h>
#include <structs.h>
#include <memory.h>

// Our MU0 VM!
int dispatch(FILE * fp, FILE * hp) {
    int error_code = 0;
    heap_t heap;
    uint16_t * code;

    // Make a heap and code-space if both were passed
    if (hp) {
        create_heap(&heap, hp);
        create_codespace(&code, fp);    
    } else { //If no heap-file,sssume codefile is also heap
        create_heap(&heap, fp);
        code = heap.heap;
    }

    if (!heap.heap) {
        printf("VM Error: Heap did not allocate!");
        return -4;
    }

    // Lets run code
    if (code) {
        // Ok lets setup our initial registers
        uint16_t registers[3] = {0};

        // Include our targeting macro and targets
        #include <target_def.h>
        #include <targets.h>
        
        // Our main VM loop
        while(1) {
            DISPATCH:
            // Fetch the current instruction
            registers[REG_IR] = code[registers[REG_PC]];
            operation_struct* op = (operation_struct *)(&registers[REG_IR]);

            // Little inspection
            printf("PC: %i, ACC: %i, op: %#X, s: %#X ", 
                registers[REG_PC], registers[REG_ACC],
                (*op).opcode, (*op).s);

            // Point PC to the next instruction
            registers[REG_PC]++;

            // This is where the magic happens
            goto *op_targets[(*op).opcode];

            // We will never evaluate this time consuming switch
            // because of computed-goto awesome
            switch((*op).opcode) {
                TARGET(OP_LDA) // ACC := mem[S]
                HEAP_CHECK((*op).s)
                printf("LDA\n");
                registers[REG_ACC] = heap.heap[(*op).s];
                goto DISPATCH;

                TARGET(OP_STO) // mem[S] := ACC
                HEAP_CHECK((*op).s)
                heap.heap[(*op).s] = registers[REG_ACC];
                printf("STO\n");
                goto DISPATCH;

                TARGET(OP_ADD) // ACC := ACC + mem[S]
                HEAP_CHECK((*op).s)
                printf("ADD\n");
                registers[REG_ACC] += heap.heap[(*op).s];
                goto DISPATCH;

                TARGET(OP_SUB) // ACC := ACC - mem[S]
                HEAP_CHECK((*op).s)
                registers[REG_ACC] -= heap.heap[(*op).s];
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

            TARGET_HEAP_BLOWOUT: // Blew out the heap
            printf("HEAP BLOWOUT\n");
            error_code = -8;
            break;

            TARGET_OP_STP: // Normal Stop
            printf("STP\n");
            error_code = 0;
            break;
        }
    }

    if (code) free(code);
    if (heap.heap) free(heap.heap);

    return error_code;
}

// Main entry point
void main(int argc, char * argv[]) {
    // do an argument check
    if (argc < 2 || argc > 3) {
        printf("Usage: mu0 bitfile [heapfile]\n");
        exit(1);
    }
    
    // Lets open our bytecode file
    FILE * fd = fopen(argv[1], "rb");
    if (!fd) {
        printf("Cannot access bytecode file!\n");
        exit(127);
    }

    FILE * hd;
    if (argc == 3) {
        // Lets open our heap file
        hd = fopen(argv[2], "rb");
        if (!hd) {
            printf("Cannot access heapfile!\n");
            exit(127);
        }
    }

    // Lets do this thing!
    int err_code = dispatch(fd, hd);

    // Close our bytecode files
    if (fd) fclose(fd);
    if (hd) fclose(hd);

    // Print an error code if needed
    if (err_code != 0) {
        printf("VM failed with error code: %i\n", err_code);
    }

    exit(0);
}
