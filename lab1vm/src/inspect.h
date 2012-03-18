/*
 * Inspection function header
 *
 * Greg Jurman <gdj2214@rit.edu>
 */

#ifndef INSPECT_H_
#define INSPECT_H_

#include "structs.h"
#include <stdio.h>

void inspect_cmd_struct(cmd_struct c);
void inspect_data_struct(data_struct d);
void inspect_registers(char registers[]);
#endif
