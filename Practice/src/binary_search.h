
#ifndef CPP_WS_BINARY_SEARCH_H_
#define CPP_WS_BINARY_SEARCH_H_

#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;

namespace BINARY_SEARCH {

/**
 * 有序整型数组查找指定value的位置，二分查找
 * https://baike.baidu.com/item/二分查找/10628618?fr=aladdin
 * @param data
 * @return 查找成功
 */
int binary_search(vector<int> &data, int value) {
    int start = 0;
    int end = data.size();

    while (start <= end) {
        int mid = (end + start) / 2;
        int cur = data[mid];

        if (value < cur) {
            end = mid - 1;
        } else if (value > cur) {
            start = mid + 1;
        } else {
            return mid;
        }
    }

    return -1;
}

void input() {
    int value;
    cin >> value;
    cout << "Search: " << value << endl;

    vector<int> sort_data;
    int input_data;
    while (cin >> input_data) {
        if (input_data == '\n') {
            break;
        }

        sort_data.push_back(input_data);
    }

    cout << "Sorted array: " << endl;
    for (auto data : sort_data) {
        cout << data << "  ";
    }
    cout << endl;

    int pos = binary_search(sort_data, value);
    if (pos >= 0) {
        cout << "Find " << value << " ,Position is " << pos << endl;
    } else {
        cout << "Can't find " << value << endl;
    }
}

}  // BINARY_SEARCH

#endif //CPP_WS_BINARY_SEARCH_H_
