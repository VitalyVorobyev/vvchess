#! /usr/bin/env python

import glob
import os
import subprocess


def init():
    dirs = ['./build', './build/obj']
    for item in dirs:
        if not os.path.isdir(item):
            os.mkdir(item)
    os.chdir('./build')


def get_sources(path='../src'):
    return glob.glob(f'{path}/*.cpp')


def gcc_precompile_cmd(flags=['fmodules-ts', 'std=c++20', 'c']):
    return ' '.join(['gcc-11'] + list(map(lambda x: f'-{x}', flags)))


def precompile(src, compiler='gcc'):
    cmd = gcc_precompile_cmd().split()
    for file in src:
        print(' '.join(cmd + [file]))
        subprocess.run(cmd + [file])


def main():
    init()
    src = get_sources()
    precompile(src)


if __name__ == '__main__':
    main()
