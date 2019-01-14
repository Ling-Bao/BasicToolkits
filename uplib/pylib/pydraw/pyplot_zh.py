#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
@Author: Ling Bao
@Description: Solve chinese messy code when using matplotlib

@data: 2018/9/12
@version: V1.0.0
"""


def help_me():
    """
    Help to solve chinese messy code when using matplotlib
    :return: None
    """
    split_line("pyplot_zh help")
    instructions = "from pyplotz.pyplotz import plt\n" \
                   "from pyplotz.pyplotz import PyplotZ\n" \
                   "pltz = PyplotZ()\n" \
                   "pltz.enable_chinese()\n\n" \
                   "detail help: https://www.jianshu.com/p/aecaf11bcd0d"
    print(instructions)
    split_line("pyplot_zh help")


def split_line(keywords=""):
    """
    special split line for print
    :param keywords: key description
    :return: None
    """
    print("_________________________________%s_________________________________" % keywords)
