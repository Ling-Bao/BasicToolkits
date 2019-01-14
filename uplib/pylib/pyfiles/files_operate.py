#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
@Author: Ling Bao
@Description: Files or directory operation

@data: 2018/9/12
@version: V1.0.0
"""

import os
import shutil


def get_files_by_suffix(file_path, suffix='.jpg'):
    """
    Get files by suffix
    :param file_path: directory including files
    :param suffix: if suffix == ".*", return all files
    :return: file lists satisfied suffix requirement
    """
    file_lists = []
    for root, dirs, files in os.walk(file_path):
        for file in files:
            if ".*" == suffix:
                file_lists.append(os.path.join(root, file))
            elif os.path.splitext(file)[1] == suffix:
                file_lists.append(os.path.join(root, file))

    return file_lists


def delete_by_requirement(dir_path, requirement="*"):
    """
    Delete file or directory by requirements
    :param dir_path: directory path
    :param requirement: file name or directory name, if requirement == "*", delete all files and directory
    :return: None
    """
    for root, dirs, files in os.walk(dir_path):
        print(root, dirs, files)
        for dir_name in dirs:
            if dir_name == requirement:
                print("delete directory:%s/%s" % (root, dir_name))
                shutil.rmtree(os.path.join(root, dir_name))

        for file_name in files:
            if file_name == requirement:
                print("delete directory:%s/%s" % (root, file_name))
                os.remove(os.path.join(root, file_name))
