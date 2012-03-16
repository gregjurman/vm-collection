"""
    This is our simple compiler for our example virtual-machine.

    Usage:
        python compiler.py in-file out-file

    This compiler is really simple because we have (and only have)
    16-bit commands, and our VM is only 4-bits wide for data and
    2-bits for addressing.
"""

import struct
import re
import argparse

# Define our opcode mapping
opcodes = { #op, src, dest
    'MOV' : (0, [('reg', 'reg')]), # Copy from one reg to another
    'ST' : (1, [('reg', None)]),   # Store (to display/output)
    'LI' : (2, [('num', 'reg')]),  # Load Immediate
    'DIS' : (3, [('num', None)]),  # Store to output
    }

class CompilerError(Exception):
    pass


def pack_data(input_val):
    if not input_val in range(0, 16):
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

        g['arg1'] = parse_argument(g['arg1']) if g['arg1'] else (None, None)
        g['arg2'] = parse_argument(g['arg2']) if g['arg2'] else (None, None)

        return g


def make_bytecode(asm_line):
    asm_dict = parse_operation(asm_line)
    
    if not asm_dict:
        raise CompilerError('line is not valid')

    arg_tuple = (asm_dict['arg1'][0], asm_dict['arg2'][0])
    val_tuple = (asm_dict['arg1'][1], asm_dict['arg2'][1])

    if not arg_tuple in opcodes[asm_dict['op']][1]:
        raise CompilerError('incorrect arguments for %s' % asm_dict['op'])
    
    op = asm_dict['op']

    src = 0
    data = 0
    if 'reg' == arg_tuple[0]:
        src = val_tuple[0]
        data = 0
    elif 'num' == arg_tuple[0]:
        src = 0
        data = val_tuple[0]
   
    dest = 0 
    if 'reg' == arg_tuple[1]:
        dest = val_tuple[1]
    elif 'num' == arg_tuple[1]:
        dest = 0
    
    print op, src, dest, data

    pdata = pack_data(int(data))
    pcmd = pack_cmd(op, int(src), int(dest))

    return struct.pack('BB', pcmd, pdata)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('in_file', type=str)
    parser.add_argument('out_file', type=str)

    args = parser.parse_args()

    with open(args.in_file, 'r') as in_file:
        with open(args.out_file, 'w') as out_file:
            for l in in_file:
                try:
                    out_file.write(make_bytecode(l))
                except CompilerError as ce:
                    print str(ce), l
                    break
