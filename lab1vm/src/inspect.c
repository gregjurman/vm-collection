#include "inspect.h"

void inspect_cmd_struct(cmd_struct c) {
    printf("\topcode: %i, src: %i, dest: %i\n", 
        c.opcode, c.src, c.dest);
}

void inspect_data_struct(data_struct d) {
    printf("\tinput: %i, output: %i\n",
        d.input, d.output);
}

void inspect_registers(char registers[]) {
    // Being lazy and not bothering looping
    printf("\tCurrent registers: %i %i %i %i\n", 
        registers[0], registers[1],
        registers[2], registers[3]);
}
