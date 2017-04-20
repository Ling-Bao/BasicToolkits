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
* @ copyright LingMin Technology 2017 -
*
*************************************************************************/

// C library


// C++ Library
#include <cstring>
#include <iostream>
using std::cout;
using std::endl;


// Others Library


// Project Library
#include "SortAlgorithm/SortSelf.h"


// Pre-Definition
#define TypeValue double


int main() {
    cout << endl << "OK, Starting my testing time!" << endl << endl;


/********************************交换函数********************************/
    cout << endl << "********************************交换函数********************************" << endl;
//    测试1，swap函数
    cout << "*********测试1，swap函数*********" << endl;
    int a = 2;
    int b = 3;
    cout << "交换数值：Pre a = " << a << "\tb = " << b << endl;
    SwapTool(&a, &b);
    cout << "交换数值：Pre a = " << a << "\tb = " << b << endl << endl;

//    测试2，swap函数
    cout << "*********测试2，swap函数*********" << endl;
    int array[] = {1, 2, 3, 4, 5};
    cout << "交换数组元素：Pre array = ";
    printArray(array, getArrayLen(array));
    SwapTool(array, 3, 4);
    cout << "交换数组元素：Post array = ";
    printArray(array, getArrayLen(array));
    cout << endl;


/********************************测试数据********************************/
    //int Array[] = {10, 1, 5, 7, 9, 1, 4, 6, 8, 23, 65, 345, 90, 21, 75, 34, 61, 12, 3, 8, 76};
    TypeValue Array[] = {1.2, 5.6, 7, 9.3, 0.1, 3.4, 6, 6.1, 1.3, 5.0, 7.5, 9, 1.3, 4.1, 6.8, 8.9};
    int lengthArray = getArrayLen(Array);

    cout << endl << "********************************测试数据********************************" << endl;
    printArray(Array, lengthArray);


/********************************插入排序********************************/
    cout << endl << "********************************插入排序********************************" << endl;
//    测试3，插入排序
    cout << "*********测试3，插入排序*********" << endl;
    TypeValue* insertArray = new TypeValue[lengthArray];
    memcpy(insertArray, Array, sizeof(Array));
    printArray(insertArray, lengthArray);
    InsertSort(insertArray, lengthArray);
    cout << "插入排序：Post array = ";
    printArray(insertArray, lengthArray);
    cout << endl;
    delete insertArray;

//    测试4，Shell增量希尔排序
    cout<< "*********测试4，Shell增量希尔排序*********" << endl;
    TypeValue* shellArray = new TypeValue[lengthArray];
    memcpy(shellArray, Array, sizeof(Array));
    ShellSort(shellArray, lengthArray, "Shell");
    cout << "希尔排序：Post array = ";
    printArray(shellArray, lengthArray);
    cout << endl;
    delete shellArray;

//    测试5，Hibbard增量希尔排序
    cout << "*********测试5，Hibbard增量希尔排序*********" << endl;
    TypeValue* hsArray = new TypeValue[lengthArray];
    memcpy(hsArray, Array, sizeof(Array));
    ShellSort(hsArray, lengthArray, "Hibbard");
    cout << "希尔排序：Post array = ";
    printArray(hsArray, lengthArray);
    cout << endl;
    delete hsArray;


/********************************选择排序********************************/
    cout << endl << "********************************选择排序********************************" << endl;
//    测试6，选择排序
    cout << "*********测试6，选择排序*********" << endl;
    TypeValue* selectArray = new TypeValue[lengthArray];
    memcpy(selectArray, Array, sizeof(Array));
    SelectSort(selectArray, lengthArray);
    cout << "选择排序：Post array = ";
    printArray(selectArray, lengthArray);
    cout << endl;
    delete selectArray;

//    测试7，堆排序
    cout<< "*********测试7，堆排序*********" << endl;
    TypeValue* heapArray = new TypeValue[lengthArray];
    memcpy(heapArray, Array, sizeof(Array));
    HeapSort(heapArray, lengthArray);
    cout << "堆排序：Post array = ";
    printArray(heapArray, lengthArray);
    cout << endl;
    delete heapArray;


/********************************交换排序********************************/
    cout << endl << "********************************交换排序********************************" << endl;
//    测试8，冒泡排序
    cout<< "*********测试8，冒泡排序*********" << endl;
    TypeValue* bubbleArray = new TypeValue[lengthArray];
    memcpy(bubbleArray, Array, sizeof(Array));
    BubbleSort(bubbleArray, lengthArray);
    cout << "冒泡排序：Post array = ";
    printArray(bubbleArray, lengthArray);
    cout << endl;
    delete bubbleArray;

//    测试9，快速排序
    cout << "*********测试9，快速排序*********" << endl;
    TypeValue* quickArray = new TypeValue[lengthArray];
    memcpy(quickArray, Array, sizeof(Array));
    QuickSort(quickArray, 0, lengthArray - 1);
    cout << "快速排序：Post array = ";
    printArray(quickArray, lengthArray);
    cout << endl;
    delete quickArray;


/********************************归并排序********************************/
    cout << endl << "********************************归并排序********************************" << endl;
//    测试10，归并排序
    cout << "*********测试10，归并排序*********" << endl;
    TypeValue* mergeArray = new TypeValue[lengthArray];
    memcpy(mergeArray, Array, sizeof(Array));
    TypeValue* mergeTempArray = new TypeValue[lengthArray];
    cout << "归并排序：Pre array = ";
    printArray(mergeArray, lengthArray);
    MergeSort(mergeArray, mergeTempArray, 0, lengthArray - 1);
    cout << "归并排序：Post array = ";
    printArray(mergeArray, lengthArray);
    cout << endl;
    delete mergeArray;
    delete mergeTempArray;

    //    测试11，修正归并排序
    cout << "*********测试11，修正归并排序*********" << endl;
    TypeValue* modifyMergeArray = new TypeValue[lengthArray];
    memcpy(modifyMergeArray, Array, sizeof(Array));
    TypeValue* modifyMergeTempArray = new TypeValue[lengthArray];
    cout << "修正归并排序：Pre array = ";
    printArray(modifyMergeArray, lengthArray);
    ModifyMergeSort(modifyMergeArray, modifyMergeTempArray, 0, lengthArray - 1, 10);
    cout << "修正归并排序：Post array = ";
    printArray(modifyMergeArray, lengthArray);
    cout << endl;
    delete modifyMergeArray;
    delete modifyMergeTempArray;


    /********************************线性排序********************************/
    cout << endl << "********************************计数排序********************************" << endl;
//    测试12，计数排序
    try
    {
        int countingArray[] = {10, 1, 5, 7, 9, 1, 4, 6, 8, 23, 65, 345, 90, 21, 75, 34, 61, 12, 3, 8, 76};
        vector<int> vecI1(b, b + getArrayLen(countingArray));

        CountingSort(vecI1, 9);

        for(auto x : vecI1)
        {
            cout << x << "\t";
        }
        cout << endl;

        for_each(vecI1.begin(), vecI1.end(), Print<int>());
        cout << endl;
    }
    catch (out_of_range)
    {
        cerr << "Range Error!\n";
    }
    catch (...)
    {
        cerr << "Unknow Exception thrown\n";
    }


    return 0;
}