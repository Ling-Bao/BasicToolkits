#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
@Author: Ling Bao
@Description: Let print output to log file

@data: 2018/9/12
@version: V1.0.0
"""

import sys
import os
import time


class Logger(object):
    def __init__(self, filename="Default.log"):
        self.terminal = sys.stdout
        self.log = open(filename, "a")

    def write(self, message):
        self.terminal.write(message)
        self.log.write(message)

    def flush(self):
        pass


def print_to_file(log_file):
    """
    Setting print to log file
    :param log_file: print information is stored in this log_file
    :return: None
    """
    path = os.path.abspath(os.path.dirname(__file__))
    types = sys.getfilesystemencoding()
    sys.stdout = Logger(log_file)

    print('------------------begin testing for print logs------------------')
    print("path: " + path)
    print("encode: " + types)
    print('-------------------end testing for print logs-------------------')


def logs_msg(py_file, log_line, info):
    """
    Special format message to trace error
    :param py_file: happening error's python file
    :param log_line: happening error's line
    :param info: some notes to explain why happening error
    :return: msg
    """
    msg = "time=" + str(get_current_time()) + "||file=" + py_file + "||line=" + str(log_line) + "||info=" + info
    return msg


def logging_help():
    split_line("logging help")
    instructions = "logging.basicConfig(filename=log_file, filemode='a', level=logging.WARNING)\n" \
                   "logging.error()\n" \
                   "logging.warning()\n" \
                   "logging.debug()\n" \
                   "logging.info()\n\n" \
                   "detail help: https://docs.python.org/3/library/logging.html"
    print(instructions)
    split_line("logging help")


def get_current_time():
    """
    Get current time
    :return: current time
    """
    return time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(time.time()))


def split_line(keywords=""):
    """
    special split line for print
    :param keywords: key description
    :return: None
    """
    print("_________________________________%s_________________________________" % keywords)
