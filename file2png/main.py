#!/usr/bin/env python
import png
import argparse
import math
import sys

def parse_args():
    parser = argparse.ArgumentParser(
        description='Converts any file into a png.')
    parser.add_argument('src',
        action='store',
        type=str,
        nargs='?',
        default='-',
        help='file to read data from, defaults to "-" for stdin')
    parser.add_argument('dst',
        action='store',
        type=str,
        nargs='?',
        default='-',
        help='file to write data to, defaults to "-" for stdout')
    return parser.parse_args()

def main():
    args = parse_args()

    src_file = open(args.src, 'rb') if args.src != '-' else sys.stdin
    dst_file = open(args.dst, 'wb') if args.dst != '-' else sys.stdout

    src_data = src_file.read()

    if len(src_data) < 4:
        raise Exception(
            'src file length must be longer than 4 bytes, only '
            '{length} bytes found.'.format(length=len(src_data)))

    # calculate the nearest square root
    width = int(math.floor(math.sqrt(len(src_data))))
    size = width * width

    # chop off any extra data we're not going to use
    data = src_data[0:size]

    # convert all the characters to plain `int`s
    data = map(ord, data)

    # chop up the data into rows
    data = [
        data[i:(i+1)*width]
        for i in range(width)
    ]

    # create the png file
    w = png.Writer(width, width, greyscale=True)
    w.write(dst_file, data)

if __name__ == '__main__':
    main()
