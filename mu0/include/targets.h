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
