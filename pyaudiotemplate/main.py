#!/usr/bin/env python
#
import collections
import threading
import time
import pyaudio
import array
import time

# https://docs.python.org/2/library/array.html
# type code | c type
# 'c'  char
# 'b'  signed char
# 'B'  unsigned char
# 'u'  Py_UNICODE
# 'h'  signed short
# 'H'  unsigned short
# 'i'  signed int
# 'I'  unsigned int
# 'l'  signed long
# 'L'  unsigned long
# 'f'  float
# 'd'  double

class State(object):
    def __init__(self):
        self.running = True

def packed_zeros(size):
    return array.array('H', [0 for i in range(size)]).tostring()

def open_streams():

    pa = pyaudio.PyAudio()

    stream_input = pa.open(
          format=pyaudio.paInt16
        , channels=1
        , rate=44100
        , input=True
        #  , frames_per_buffer=512
        )

    stream_output = pa.open(
          format=pyaudio.paInt16
        , channels=1
        , rate=44100
        , output=True
        #  , frames_per_buffer=512
        )

    stream_input.start_stream()
    stream_output.start_stream()

    return (pa, stream_input, stream_output)

def thread_input_func(stream_input, ring, state):
    try:
        while state.running:
            buf = stream_input.read(1024 * 2)
            ring.append(buf)
    finally:
        state.running = False

def thread_output_func(stream_output, ring, state):
    try:
        while state.running:
            while ring:
                stream_output.write(ring.pop())
    finally:
        state.running = False

def thread_main(state):
    try:
        while state.running:
            time.sleep(10)
    finally:
        state.running = False

def main():

    pa, stream_input, stream_output = open_streams()

    ring = collections.deque(maxlen=64)

    state = State()

    thread_input = threading.Thread(target=thread_input_func, args=(stream_input, ring, state))
    thread_output = threading.Thread(target=thread_output_func, args=(stream_output, ring, state))

    thread_input.start()
    thread_output.start()

    thread_main(state)
    thread_input.join()
    thread_output.join()

if __name__ == '__main__':
    main()

