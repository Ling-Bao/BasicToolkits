#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
@Author: Ling Bao
@Description: Get current time

@data: 2018/9/12
@version: V1.0.0
"""

import time


def get_current_time():
    """
    获取系统本地时间
    :return:
    """
    return time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(time.time()))
