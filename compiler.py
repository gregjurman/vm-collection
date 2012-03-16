"""
    This is our simple compiler for our example virtual-machine.

    Usage:
        python compiler.py in-file out-file

    This compiler is really simple because we have (and only have)
    16-bit commands, and our VM is only 4-bits wide for data and
    2-bits for addressing.
"""

import array
import re

# Define our opcode mapping
opcodes = { #op, src, dest
    'MOV' : (0, [('reg', 'reg')]), # Copy from one reg to another
    'ST' : (1, [('reg', None)]),   # Store (to display/output)
    'LI' : (2, [('reg', 'num')]),  # Load Immediate
    'DIS' : (3, [('num', None)]),  # Store to output
    }

class CompilerError(Exception):
    pass


def pack_data(input_val):
    if not input_val in range(0, 15):
        raise CompilerError("data argument is not a short")

    return input_val

def pack_cmd(cmd, src, dest):
    if cmd.upper() not in opcodes.keys():
        raise CompilerError("invalid op-code")

    if not src in range(0, 4):
        raise CompilerError("source register not valid")

    if not dest in range(0, 4): 
        raise CompilerError("destination register not valid")

    out = opcodes[cmd.upper()][0]
    out = out << 2
    out = out | src
    out = out << 2
    out = out | dest
    
    return out


numerical_regex = r'#[\d]{1,2}'
register_regex = r'R[\d]{1}'

opcode_regex = r'|'.join(opcodes.keys())

reg_or_num = r'R(?P<reg>[\d]{1})|#(?P<num>[\d]{1,2})'

arg_regex = r'|'.join([numerical_regex, register_regex])
arg_set_regex = r'(?P<arg1>%s)(,[ ]{0,1}(?P<arg2>%s)){0,1}' % (arg_regex, arg_regex)

command_regex = r'(?P<op>%s) %s$' % (opcode_regex, arg_set_regex)

re_command = re.compile(command_regex)
re_reg_or_num = re.compile(reg_or_num)


def parse_argument(arg):
    match = re_reg_or_num.match(arg)

    if match:
        g = dict((k,v) for k, v in match.groupdict().iteritems() if v)

        if 'reg' in g and 'num' in g or len(g) == 0:
            raise CompilerError("cannot parse argument")

        key = g.keys()[0]

        return (key, g[key],)


def parse_operation(asm_line):
    match = re_command.match(asm_line.strip())

    if match:
        g = match.groupdict()

        g['arg1'] = parse_argument(g['arg1'])
        if g['arg2']:
            g['arg2'] = parse_argument(g['arg2'])
        else:
            del g['arg2']


        return g


def interperate_line(asm_line):
    pass

if __name__ == "__main__":
    test = """
NOPE #0, #1
ST #0,#1
ST R1,R2
DIS R0,#3
LI #3
"""
    for l in test.splitlines():
        print parse_operation(l)
