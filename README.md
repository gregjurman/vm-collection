# Greg's Virtual Machine Collection

A collection of stupid little virtual machines for the purpose of learning
how to do interpretation and optimiztion.

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


## MU0 VM - Virtual Machine for MU0

MU0 is a simple academic microcomputer that is sometimes used to present the 
basics of a microcomputer to students. This is a little VM for it.

[Link to lecture notes](http://cas.ee.ic.ac.uk/people/gac1/Architecture/Lecture2.pdf)

### Specifications

* Von Numan based architecture
* no general purpose registers
* accumulator based
* load/store based


## Cool resources
[Labels as values](http://gcc.gnu.org/onlinedocs/gcc/Labels-as-Values.html)
