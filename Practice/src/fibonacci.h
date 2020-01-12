
#ifndef CPP_WS_FIBONACCI_H_
#define CPP_WS_FIBONACCI_H_

/**
 * 斐波那契数列题目
 * 1）写一个函数，输入 n, 求斐波那契（Fibonacci）数列的第 n 项。
 * 2）一只青蛙一次可以跳上 1 级台阶，也可以跳上 2 级。求该青蛙跳上一个n级的台阶总共有多少种跳法？
 * 3）一只青蛙一次可以跳上 1 级台阶，也可以跳上 2 级，...... ，也可以跳上n级，此时该青蛙跳上一个 n 级的台阶共有多少种跳法？
 * 4）用2x1的小矩形横着或者竖着去覆盖更大的2xN矩形；请问用N个2x1小矩形无重叠地覆盖一个2xN的大矩形，总共有多少种方法？
 * 参考1：斐波那契数列（C++ 和 Python 实现），https://www.cnblogs.com/klchang/p/7857477.html
 * 参考2：斐波拉契数列的计算方法，https://www.cnblogs.com/swfpt/p/6850396.html
 * 参考3：求超大斐波那契数列|迭代法|通项公式法，https://blog.csdn.net/qq_39464369/article/details/90044190
 * f(0) = 0, f(1) = 1, f(n) = f(n-1) + f)n-2)
 */

#include <vector>
#include <iostream>

using namespace std;

namespace FIBONACCI {

/**
 * 递归实现，复杂度O(2^n)
 * @param n
 * @return
 */
int fibonacci_recursive(int n) {
    if (0 == n) return 0;
    if (1 == n) return 1;

    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
}


/**
 * 迭代实现，复杂度O(n)
 * @param n
 * @return
 */
int fibonacci_iterative(int n) {
    if (n < 2) return n;

    int n0 = 0;
    int n1 = 1;
    int tmp;

    for (int i = 2; i <= n; ++i) {
        tmp = n0;
        n0 = n1;
        n1 = tmp + n0;
    }

    return n1;
}


/**
 * 2*2方阵乘法
 * @param a 输入
 * @param b 输入
 * @param res 输出
 */
void matrix_power(vector<int> &a, vector<int> &b, vector<int> &res) {
    res[0] = a[0] * b[0] + a[1] * b[2];
    res[1] = a[0] * b[1] + a[1] * b[3];
    res[2] = a[2] * b[0] + a[3] * b[2];
    res[3] = a[2] * b[1] + a[3] * b[3];
}


/**
 * 求x指数幂
 * @param x
 * @param n
 * @return
 */
double Pow(double x, unsigned int n)
{
    double result = 1;
    while(n)
    {
        if(n & 0x01) result *= x;
        x  = x*x;
        n >>= 1;
    }
    return result;
}


/**
 * 公式法，复杂度O(logn)
 * @param n
 * @return
 */
int fibonacci_matrix_power(int n) {
    if (n <= 0) return 0;

    --n;  // 计算矩阵prod的n-1次幂

    vector<int> result = {1, 0, 1, 0};
    vector<int> prod = {1, 1, 1, 0};

    while (n) {
        // 如果n的最低二进制位为1，则乘上对应的幂次prod
        if (n & 1) matrix_power(result, prod, result);
        matrix_power(prod, prod, prod);

        n >>= 1;  // 除以2
    }

    return result[0];
}


void input() {
    // get input data
    int n;
    cin >> n;
    cout << "Input = " << n << endl;

    int result;

    // Method1: recursive method
    result = fibonacci_recursive(n);
    cout << "Recursive: Fibonacci(" << n << ") = " << result << endl;

    // Method2: iterative method
    result = fibonacci_iterative(n);
    cout << "Iterative: Fibonacci(" << n << ") = " << result << endl;

    // Method3: iterative method
    result = fibonacci_iterative(n);
    cout << "Iterative: Fibonacci(" << n << ") = " << result << endl;
}

}  // FIBONACCI


#endif //CPP_WS_FIBONACCI_H_
