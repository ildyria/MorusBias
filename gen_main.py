#!/usr/bin/env python3

from tools  import save, gen_name, bcolors
from masks import masks_list
from sys import argv

def head():
    z = ''
    z += '#pragma once\n'
    z += '\n'
    z += '#include "Utilities/utilities.h"\n'
    z += '#include "Ciphers/morus.h"\n'
    z += '\n'
    return z

def import_masks(masks_list):
    z = ''
    for i in range(len(masks_list)):
        z += '#include "Masks/masks_' + gen_name(masks_list[i]['kind'],masks_list[i]['width']) + '.h"\n'

    return z

def defines(kind,width,test):
    name = gen_name(kind,width)
    z = ''
    z += '#define STATE ' + name + '_print_state\n'
    z += '#define PRINT ' + name + '_print\n'
    z += '#define RAND ' + name + '_rand_init\n'
    z += '#define ENCR ' + name + '_encrypt\n'
    z += '#define COPY ' + name + '_copy_state\n'
    z += '#define MASK ' + name + '_' + str(test) + '\n'
    z += '#define WEIGHT ' + name + '_' + str(test) + '_weight()\n'
    return z

def switch_test(x):
    return {
        'alpha':    1,
        'beta':     2,
        'gamma':    3,
        'delta':    4,
        'epsil':    5,
        'appr1':    6,
        'appr2':    7,
        'full':     8,
    }.get(x, 8)

if __name__ == "__main__":

    test = 8
    if (len(argv) > 1):
        test = switch_test(argv[1])
    width = int(argv[2]) if len(argv) > 2 else 32
    kind = int(argv[3]) if len(argv) > 3 else 1

    valid = False
    for i in range(len(masks_list)):
        if (masks_list[i]['width'] == width and
            masks_list[i]['kind'] == kind and
            test <= len(masks_list[i]['weight'])):
            valid = True

    if valid :
        z = ''
        z += head()
        z += import_masks(masks_list)
        z += '\n'
        z += defines(kind,width,test)
        z += '\n'
        z += 'int main(int argc, char const *argv[]);\n'
        print(bcolors.YELLOW + "Generate main.h "+ bcolors.ENDC)
        save('main.h', z);
        print(bcolors.PURPLE +  z + bcolors.ENDC )

    else:
        print(bcolors.BRIGHTRED + 'TEST DOES NOT EXISTS!' + bcolors.ENDC )
