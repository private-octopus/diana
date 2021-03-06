#!/usr/bin/python
# coding=utf-8
#
# This scripts tries to estimate the variance of a few M3 test metrics.

import codecs
import sys
import m3name
import captures
import m3summary
import os
from os.path import isfile, join
import glob

def ithiwalk(file_list, path):
    for x in os.listdir(path):
        y = join(path, x)
        if isfile(y):
            file_list.append(y)
        else:
            ithiwalk(file_list, y)


# By default, we expect to test with the file "data/tiny_capture.csv, which has 589 lines.
if len(sys.argv) < 4:
    print("usage: " + sys.argv[0] + " capture.csv nb_lines sum_m3_file.csv")
    ret = -1
else:
    ret = 0

if ret == 0:
    ret = m3name.m3name_test()
    if ret == 0:
        print("m3name_test passes.")
    else:
        print("m3name_test fails.")

if ret == 0:
    ret = captures.capture_line_test()
    if (ret == 0):
        print("Capture line test passes.")
        ret = captures.capture_test(sys.argv[1], int(sys.argv[2]))
        if (ret == 0):
            print("Capture file test passes.")

if ret == 0:
    ret = m3summary.cc_to_iso3_test()
    if (ret == 0):
        print("CC to ISO3 test passes.")

if ret == 0:
    ret = m3summary.m3summary_line_test()
    if (ret == 0):
        print("M3 summary line test passes.")

if ret == 0:
    ret = m3summary.m3summary_file_test(sys.argv[3])
    if ret == 0:
        print("m3 summary file test passes")

exit(ret)