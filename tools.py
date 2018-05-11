#!/usr/bin/env python3

def save(fn, z):
    d = open(fn, 'w', encoding="utf-8")
    d.write(z)
    d.close()

def gen_name(kind,width):
    name = 'morus_'
    if kind == 1:
        name = 'mini_' + name

    if width == 32:
        name += '640'
    if width == 64:
        name += '1280'
    return name

class bcolors:
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'
    RED = '\033[31m'
    BRIGHTRED = '\033[91m'
    MAGENTA = '\033[35m'
    PURPLE = '\033[95m'
    ORANGE = '\033[33m'
    YELLOW = '\033[93m'
    BLUE = '\033[94m'
    GREEN = '\033[92m'
