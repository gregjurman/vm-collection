/*
 * Argument parser
 *
 * Greg Jurman <gdj2214@rit.edu>
 */

#include "args.h"

/* Parse a single option. */
error_t parse_opt (int key, char *arg, struct argp_state *state) {
    /* Get the input argument from argp_parse, which we
     * know is a pointer to our arguments structure. */
    struct arguments *args = (*state).input;

    switch (key)
    {
        case 'v':
            (*args).verbose = 1;
            break;

        case ARGP_KEY_ARG:
            if ((*state).arg_num >= 1)
                /* Too many arguments. */
                argp_usage (state);

            (*args).bit_file = arg;

            break;

        case ARGP_KEY_END:
            if ((*state).arg_num < 1)
                /* Not enough arguments. */
                argp_usage (state);
            break;

        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}
