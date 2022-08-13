#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
from Clicker import Clicker
from global_defs import (Resource, ResultCode)
import argparse


def main(param="hh") -> int:
    pass


if __name__ == "__main__":

    clicker: Clicker = Clicker()

    _res = int(ResultCode.UNDEF)

    descr = 'Программа для автоматизации процессов сбора информации'

    parser = argparse.ArgumentParser(description=descr)

    parser.add_argument('--clicker',
                        nargs='?',
                        help="Варианты вывода",
                        choices=['hh', 'ya'])

    parser.add_argument("-l", dest="login", default='UNDEF', type=str)
    parser.add_argument("-p", dest="password", default='UNDEF', type=str)
    parser.add_argument("-a", dest="addr", default='UNDEF', type=str)

    args = parser.parse_args()
    if args.clicker == 'hh':
        _res = clicker.auto_click(Resource.HEAD_HANTER, args.addr, args.login, args.password)
    elif args.clicker =='ya':
        pass

    sys.exit(_res)

