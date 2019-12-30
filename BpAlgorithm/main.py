# !/usr/bin/python 3
# -*- coding: utf-8 -*-

import argparse

from bp_algorithm import BpAlgorithm


def get_args():
    ap = argparse.ArgumentParser()
    ap.add_argument('-n_inputs',
                    default=3,
                    help='自变量X维数')
    ap.add_argument('-layers',
                    default=[3, 6, 3],
                    nargs='+',
                    type=int,
                    help='定义隐藏层神经元数量')
    ap.add_argument('-n_outputs',
                    default=1,
                    help='因变量Y维数')
    m_args = vars(ap.parse_args())

    return m_args


def create_fnn(m_n_inputs, m_layers, m_n_outputs):
    bp_algorithm = BpAlgorithm(m_n_inputs, layers, m_n_outputs)


if __name__ == '__main__':
    args = get_args()
    n_inputs = args['n_inputs']
    layers = args['layers']
    n_outputs = args['n_outputs']

    create_fnn(n_inputs, layers, n_outputs)
