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
opcodes = { 
    'MOV' : 0,
    'RDO' : 1,
    'WRI' : 2,
    'DIS' : 3,
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

    out = opcodes[cmd.upper()]
    out = out << 2
    out = out | src
    out = out << 2
    out = out | dest
    
    return out


numerical_regex = r'[\d]{1,2}'
register_regex = r'R[\d]{1}'

opcode_regex = r'|'.join(opcodes.keys())

reg_or_num = r'(?P<reg>%s)|(?P<num>%s)' % (register_regex, numerical_regex)

arg_regex = r'|'.join([numerical_regex, register_regex])
arg_set_regex = r'(?P<arg1>%s),[ ]{0,1}(?P<arg2>%s)' % (arg_regex, arg_regex)

command_regex = r'(?P<op>%s) %s$' % (opcode_regex, arg_set_regex)

re_command = re.compile(command_regex)
re_reg_or_num = re.compile(reg_or_num)

print reg_or_num

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
        g['arg2'] = parse_argument(g['arg2'])

        return g


if __name__ == "__main__":
    test = """
WRI 0, 1
WRI 0,1
WRI R1,R2
WRI R0,3
WRI 3,R0
"""

    for l in test.splitlines():
        print parse_operation(l)
