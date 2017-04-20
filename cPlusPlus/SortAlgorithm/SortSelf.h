/************************************************************************
*
* @description: 各种排序算法的C++ API头文件
*
* @author:      Ling Bao
* @date:        2017.02.11
*
* @last modified author:
* @last modified date:
*
* @ copyend LingMin Technology 2017 -
*
*************************************************************************/


#ifndef CPLUSPLUS_SORTSELF_H
#define CPLUSPLUS_SORTSELF_H


// C library


// C++ Library
#include <vector>
#include <algorithm>
using namespace std;


// Others Library


// Project Library
#include "../ToolsSelf/SortTools.h"


/********************************插入排序********************************/
// 插入排序
template <typename IST>
void InsertSort(IST* pData, int length)
{
    if (pData == nullptr || length == 0)
    {
        printf("Array is not NULL\n");
        return;
    }

    for (int i = 1; i < length; i++) // 假设第一个位置正确
    {
        int j = i; // 待插入元素索引及值
        IST temp = pData[i];

        // 后移
        for ( ; j > 0 && temp < pData[j - 1]; j--)
        {
            pData[j] = pData[j - 1];
        }

        // 插入
        pData[j] = temp;
    }

    return;
}


// 希尔（Shell）排序
// @param pData: 待排数组
// @param length: 待排数组长度
// @param method: 包括“Hibbard”及“Shell”；“Hibbard”为希伯德增量，“Shell”为希尔增量
// @return 无
template <typename SST>
void ShellSort(SST* pData, int length, std::string method="Hibbard")
{
    if (pData == nullptr || length == 0)
    {
        printf("Array is not NULL\n");
        return;
    }

    int delta;

    if (method.compare("Hibbard") == 0)
    {
        printf("开始利用Hibbard增量进行希尔排序！\n");

        // Hibbard增量序列公式
        delta = (length + 1) / 2 - 1;

        // 不断改变增量，对数组迭代分组进行直接插入排序，直至增量为1
        while (delta > 0)
        {
            for (int i = 0; i < delta; ++i)
            {
                ShellInsert(pData, i, delta, length);
            }

            delta = (delta + 1) / 2 - 1;
        }
    }
    else if (method.compare("Shell") == 0)
    {
        printf("开始利用Shell增量进行希尔排序！\n");

        // 希尔增量序列公式
        delta = length / 2;

        // 不断改变增量，对数组迭代分组进行直接插入排序，直至增量为1
        while (delta > 0)
        {
            for (int i = 0; i < delta; ++i)
            {
                ShellInsert(pData, i, delta, length);
            }

            delta /= 2;
        }
    }
    else
    {
        printf("没有该增量方法\n");
    }

    return;
}


/********************************选择排序********************************/
// 选择排序
template <typename SST>
void SelectSort(SST* pData, int length)
{
    if (pData == nullptr || length == 0)
    {
        printf("Array is not NULL");
        return;
    }

    int minIndex = 0;
    for (int i = 0; i < length - 1; i++)
    {
        minIndex = i;
        for (int j = i + 1; j < length; j++)
        {
            if (pData[j] < pData[minIndex])
            {
                minIndex = j;
            }
        }

        if (minIndex != i)
        {
            SwapTool(pData, i, minIndex);
        }
    }

    return;
}


// 堆排序
// @param pData: 待排序数组
// @param length: 数组长度
// @return 无
template <typename HST>
void HeapSort(HST* pData, int length)
{
    if (pData == nullptr || length == 0)
    {
        printf("Array is not NULL\n");
        return;
    }

    HST temp;

    BuildMaxHeap(pData, length); // 构建初始堆

    for (int i = length - 1; i >= 1; i--)
    {
        // 交换根节点和数组的最后一个节点
        temp = pData[i];
        pData[i] = pData[0];
        pData[0] = temp;
        // SwapTool(&pData[i], &pData[0]);

        // 筛选
        MaxHeapAdjust(pData, 0, i - 1);
    }

    return;
}


/********************************交换排序********************************/
// 冒泡排序
template <typename BST>
void BubbleSort(BST* pData, int length)
{
    if (pData == nullptr || length == 0)
    {
        printf("Array is not NULL");
        return;
    }

    for (int i = 0; i < length - 1; i++)
    {
        for (int j = length - 1; j > i; j--)
        {
            if (pData[j] < pData[j - 1])
            {
                SwapTool(pData, j, j - 1);
            }
        }
    }

    return;
}


// 快速排序；注意：初始传入参数必须“start”小于“end”
// @param pData: 待排序数组
// @param start: 起始元素索引
// @param end: 终止元素索引
template <typename QST>
void QuickSort(QST* pData, int start, int end)
{
    if (start >= end)
    {
        return;
    }

    // 二分
    int pivotPos = PartitionTool(pData, start, end);

    // 递归
    QuickSort(pData, start, pivotPos - 1);
    QuickSort(pData, pivotPos + 1, end);
}


/********************************归并排序********************************/
// 用于实现归并排序的归并操作
// @param pData: 待排序数组
// @param tempData: 保存归并结果数组
// @param left: 待归并数组起始索引
// @param middle: 待归并数组中间索引
// @param right: 待归并数组终止索引
// @return 无
template <typename MT>
void Merge(MT* pData, MT* tempData, int left, int middle, int right)
{
    int i = left;
    int j = middle;
    int m = middle + 1;
    int n = right;
    int k = 0;

    // 归并操作
    while (i <= j && m <= n)
    {
        if (pData[i] <= pData[m])
        {
            tempData[k++] = pData[i++];
        }
        else
        {
            tempData[k++] = pData[m++];
        }
    }

    while (i <= j)
    {
        tempData[k++] = pData[i++];
    }

    while (m <= n)
    {
        tempData[k++] = pData[m++];
    }

    // 归并后将结果拷贝到原数组中
    for (i = 0; i < k; ++i) {
        pData[left + i] = tempData[i];
    }
}


// 归并排序
// @param pData: 待排序数组
// @param tempData: 保存数组排序结果
// @param left: 待归并数组起始索引
// @param right: 待归并数组终止索引
// @return 无
template <typename MST>
void MergeSort(MST* pData, MST* tempData, int left, int right)
{
    if (left < right)
    {
        int middle = (left + right) / 2;

        MergeSort(pData, tempData, left, middle);
        MergeSort(pData, tempData, middle + 1, right);
        Merge(pData, tempData, left, middle, right);
    }
}


// 改进归并排序
// 详细描述：在归并排序算法中，当子问题足够小时，采用插入排序算法就较合适；注意：此函数默认子问题小于50个元素的数组进行插入排序。
// @param pData: 待排序数组
// @param tempData: 保存数组排序结果
// @param left: 待归并数组起始索引
// @param right: 待归并数组终止索引
// @return 无
template <typename MMST>
void ModifyMergeSort(MMST* pData, MMST* tempData, int left, int right, int minNumber=50)
{
    if ((right - left) >= minNumber)
    {
        int middle = (left + right) / 2;

        MergeSort(pData, tempData, left, middle);
        MergeSort(pData, tempData, middle + 1, right);
        Merge(pData, tempData, left, middle, right);
    }
    else
    {
        InsertSort(pData + left, right - left + 1);
    }
}


/********************************线性排序********************************/
// 计数排序
// @param pData: 待排序数组
// @param tempData: 保存归并结果数组
// @param left: 待归并数组起始索引
// @param middle: 待归并数组中间索引
// @param right: 待归并数组终止索引
// @return 无
void CountingSort(vector<int> &ib, vector<int> &ia, int maxElement)
{
    vector<int> ic;
    int i = 0;
    ic.resize(maxElement +1, 0);

    for(auto x : ia)
    {
        ic[x]++;
    }

    for (i = 0; i <= maxElement; i++)
    {
        ic[i] += ic[i - 1];
    }

    for (i = ia.size() - 1; i >= 0; i--)
    {
        ib[ic[ia[i]] - 1] = ia[i];
        ic[ia[i]]--;
    }
}
void CountingSort(vector<int> &ia, int maxElement)
{
    vector<int> ib(ia);
    CountingSort(ia, ib, maxElement);
}


#endif //CPLUSPLUS_SORTSELF_H