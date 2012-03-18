#include <argp.h>

#ifndef ARGS_H_
#define ARGS_H_
static error_t parse_opt (int key, char *arg, struct argp_state *state);

/* Used by main to communicate with parse_opt. */
struct arguments {
    int verbose;
    char *bit_file;
};

#ifdef NO_ARGHEADER
const char doc[] =
    "an example virtual machine for Lab 1 of RIT 0618.303.";

const char *argp_program_version =
    "lab1vm 1.0";

const char *argp_program_bug_address =
    "<gdj2214@rit.edu>";

static char args_doc[] = "bitfile";

/* The options we understand. */
static struct argp_option options[] = {
    {"verbose",  'v', 0, 0,  "Produce verbose output" },
    { 0 }
};

static struct argp argp = { options, parse_opt, args_doc, doc };
#endif

#endif
