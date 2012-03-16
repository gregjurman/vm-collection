
/* target_def.h - Defines the TARGET pre-processor macro
 *
 *
 * Greg Jurman <gdj2214@rit.edu>
 *
 * This defines how GCC contructs our switch statement
 * 
 * When you wrap one of our opcodes with TARGET() GCC will fill in the
 * blanks with the definition below.
 *
 * Example:
 *
 * `TARGET(OP_DISPLAY)` will become:
 * 
 * `TARGET_OP_DISPLAY:
 *  case OP_DISPLAY:`
 *
 * This is why we do not add a case statement or : after TARGET() as it
 * becomes filled in for us before the compiler does it's thing 
 * (hence being a pre-processor command).
 *
 * Example:
 *
 * `TARGET(OP_DISPLAY)
 *  printf("%i", op.data.input);
 *  break;`
 *
 * becomes:
 *
 * `TARGET_OP_DISPLAY:
 *  case OP_DISPLAY:
 *  printf("%i", op.data.input);
 *  break;`
**/

#define TARGET(op) \
    TARGET_##op: \
    case op: 
