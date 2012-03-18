/*
 * Defines the command structures for the VM
 *
 * Greg Jurman <gdj2214@rit.edu>
 */

#ifndef STRUCTS_H_
#define STRUCTS_H_

//Define our command struct
typedef struct {
    unsigned char dest : 2;
    unsigned char src : 2;
    unsigned char opcode : 2;
    unsigned char padding : 2;
} cmd_struct;

// Data structure
typedef struct {
    unsigned char input : 4;
    unsigned char output : 4; //We never use these
} data_struct;

// Define our complete operation struct
typedef struct {
    cmd_struct cmd;
    data_struct data;
} operation_struct;

#endif
