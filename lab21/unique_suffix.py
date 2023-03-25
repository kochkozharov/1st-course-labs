#!/usr/bin/env python

from os import walk
from os.path import splitext
from sys import argv
from collections import Counter

def main(root:str="."):
    c = Counter()
    for (a, b, filenames) in walk(root):
        for filename in filenames:
            _,suffix  = splitext(filename)
            suffix = suffix[1:]
            if suffix:
              c[suffix] += 1
    l = c.most_common()
    if l == []:
        raise Exception('Directory not found!')
    for sfx, n in l:
        print('     ',n, sfx)


if __name__ == '__main__':
    if len(argv) >= 2:
        arg=argv[1]
    else:
        arg='.'
    help = 'unique_suffix.sh [DIR] finds and counts all of the distinct file suffixes in a [DIR] recursively. Default [DIR] is a current directory.'

    if arg == '--help' or arg=='-h':
        print(help)
    else:
        main(arg)