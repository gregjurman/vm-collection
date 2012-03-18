#ifndef OPCODES_H_
#define OPCODES_H_
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

#endif
