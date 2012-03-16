# Greg's Virtual Machine Collection

## Lab 1 VM - Virtual Machine Example for 0618.303

This is an example virtual machine for Lab 1 of 0618.303 (Microcomputers).

It is a very basic introduction to processing opcodes and simple optimization
using GCC.

### Specifications

* Four 4-bit registers
* 4 operations, no Program Counter
* Pretty useless

### Op-codes

* __MOV Rsrc, Rdest__ - Copy value from src register to dest register
    * MOV R1, R3 - Copy value from R1 to R3
* __ST Rsrc__ - 'Store to memory' (in this case print to stdio)
    * ST R3 - Print R3 to stdio
* __LI #val, Rdest__ - Load the immediate value into dest register
    * LI #3, R1 - Load the number 3 into R1
* __DIS #val__ - Print the immediate value
    * DIS #5 - Print the number 5 to stdio

## Cool resources
[Labels as values](http://gcc.gnu.org/onlinedocs/gcc/Labels-as-Values.html)
