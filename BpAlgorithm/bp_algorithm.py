# !/usr/bin/python 3
# -*- coding: utf-8 -*-

import random


class BpAlgorithm(object):
    def __init__(self, n_inputs, layers, n_outputs):
        """
        通过参数初始化FNN网络
        Args:
            n_inputs: [N] a scalar, 自变量X的维数
            layers: [L1, L2, ..., Lq] a list, Li代表第i层包含的神经元数量
            n_outputs: [M] a scalar, 因变量Y的维数
        """
        # 成员变量
        self.n_inputs = n_inputs
        self.layers = layers
        self.n_outputs = n_outputs

        # 初始化FNN网络
        self.init_networks()

    def init_networks(self):
        """
        网络初始化FNN各层参数，包括权重矩阵和偏置项
        Returns:

        """
        network = list()

        # 初始化隐藏层
        n_inputs = self.n_inputs
        for l, n_neurons in enumerate(self.layers):
            # 初始化第l层参数 ==> [n_neurons, n_inputs] is list
            hidden_layer = [{'weights': [random.random() for _ in range(n_inputs + 1)]} for _ in range(n_neurons)]
            network.append(hidden_layer)

            # 第l层输出是第l+1层的输入
            n_inputs = n_neurons

        # 初始化输出层，方法同隐藏层
        hidden_layer = [{'weights': [random.random() for _ in range(n_inputs + 1)]} for _ in range(self.n_outputs)]
        network.append(hidden_layer)

        return network
