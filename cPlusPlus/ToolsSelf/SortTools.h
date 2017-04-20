/************************************************************************
*
* @description: 排序算法的所需工具的头文件
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

#ifndef CPLUSPLUS_SORTTOOLS_H
#define CPLUSPLUS_SORTTOOLS_H


// C library


// C++ Library


// Others Library


// Project Library


// 获取数组长度
template <typename T>
int getArrayLen(T& array)
{
    return (sizeof(array) / sizeof(array[0]));
}


// 求数组中值最大的元素索引及值


// 打印数组
template <typename PT>
void printArray(PT* pData, int length)
{
    for (int i = 0; i < length; ++i)
    {
        std::cout << '\t' << pData[i];
    }
    std::cout << std::endl;
}


// 打印类
template <typename T>
class Print
{
public:
    Print(){}
    void inline operator()(const T& x) const { std::cout << x << "\t";}
};


// 交换两变量的值
template <typename SWT>
void SwapTool(SWT* data1, SWT* data2)
{
    SWT tmp = 0;

    tmp = *data1;
    *data1 = *data2;
    *data2 = tmp;
}


// 交换数组两指定下标的元素
template <typename SWT>
void SwapTool(SWT* pData, int i, int j)
{
    SWT tmp = 0;

    tmp = pData[i];
    pData[i] = pData[j];
    pData[j] = tmp;
}


// 数组划分
// 详细功能：以数组第一个元素为轴，使轴左边元素均小于轴元素、右边元素均大于轴元素；注意：先从右进行扫描。
// @param pData: 待划分数组
// @param start: 轴元素
// @param end: 右索引
// @return 轴元素所在索引，返回-1代表start大于end异常
template <typename PT>
int PartitionTool(PT* pData, int start, int end)
{
    if (start > end)
    {
        printf("Parameter of \"start\" must greater than \"end\"!\n");

        return -1;
    }

    PT pivotValue = pData[start];

    while (start < end)
    {
        // 从右扫描，寻找小于pivotVale的第一个元素
        while (start < end && pData[end] >= pivotValue)
        {
            end--;
        }

        pData[start] = pData[end]; // 把小的移到左边

        // 从左扫描，寻找大于pivotVale的第一个元素
        while (start < end && pData[start] <= pivotValue)
        {
            start++;
        }

        pData[end] = pData[start]; // 把大的移到右边
    }

    pData[start] = pivotValue;

    return start;
}


// 对大顶堆性质进行维护或堆筛选（递归实现），该函数应被建堆函数BuildMaxHeap()调用
// 详细功能：除了start之外，(start + 1)~end均满足大顶堆的定义
// @param pData: 待调整数组
// @param start: 起始索引
// @param end: 结束索引
// @return 无
template <typename MHAT>
void MaxHeapAdjust(MHAT* pData, int start, int end)
{
    int lChild = 2 * start + 1;
    int rChild = lChild + 1;
    int largestIndex;

    MHAT temp;

    // 选择当前堆顶元素与左右孩子节点较大者交换
    largestIndex = (lChild <= end && pData[lChild] > pData[start]) ? lChild : start;
    if (rChild <= end && pData[rChild] > pData[largestIndex])
    {
        largestIndex = rChild;
    }

    // 选择当前堆顶元素与左右孩子节点较大者（大顶堆）交换，直至叶子节点
    if (largestIndex != start)
    {
        temp = pData[start];
        pData[start] = pData[largestIndex];
        pData[largestIndex] = temp;
        // SwapTool(&pData[start], &pData[largestIndex]);

        MaxHeapAdjust(pData, largestIndex, end);
    }
}


// 构建最大堆
// 详细功能：由初始无序序列建成一个堆需要自底向上，从第一个非叶元素开始挨个调整成一个堆
// @param pData: 待建堆数组
// @param start: 起始索引
// @param end: 结束索引
// @return 无
template <typename BMHT>
void BuildMaxHeap(BMHT* pData, int length)
{
    for (int i = length / 2 - 1; i >= 0; i--)
    {
        MaxHeapAdjust(pData, i, length - 1);
    }
}


// 希尔（Shell）排序的一趟插入
// @param pData: 待排数组
// @param start: 排序区域的起始边界
// @param delta: 增量
// @param length: 带排序数组长度
// @return 无
template <typename SIT>
void ShellInsert(SIT* pData, int start, int delta, int length)
{
    SIT temp;

    for (int i = start + delta; i < length; i += delta)
    {
        int j = i; // 待插入元素索引及值
        temp = pData[i];

        // 后移
        for ( ; j > (delta - 1) && temp < pData[j - delta] ; j -= delta)
        {
            pData[j] = pData[j - delta];
        }

        // 插入
        pData[j] = temp;
    }
}


#endif //CPLUSPLUS_SORTTOOLS_H