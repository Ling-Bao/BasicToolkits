
#ifndef CPP_WS_FIND_K_NODE_H_
#define CPP_WS_FIND_K_NODE_H_

#include <vector>
#include <iostream>

using namespace std;


namespace FIND_K_NODE {

struct ListNode {
    int m_value;
    ListNode *m_pNext;
};

ListNode *build_list(vector<int> &data) {
    ListNode *head = nullptr;
    auto *cur = new ListNode();

    for (auto item : data) {
        auto *tmp = new ListNode();
        tmp->m_value = item;
        tmp->m_pNext = nullptr;

        if (head == nullptr) {
            head = tmp;
            cur = head;
        } else {
            cur->m_pNext = tmp;
            cur = cur->m_pNext;
        }
    }

    return head;
}

/**
 * 查找链表的倒数第k个节点（双指针，边界条件）
 * https://blog.csdn.net/isluckyguo/article/details/84276233
 * @param pListHead
 * @param k
 * @return
 */
ListNode *find_k_node(ListNode *pListHead, int k) {
    if (pListHead == nullptr || k == 0) {
        return nullptr;
    }

    ListNode *cur = pListHead;
    for (int i = 0; i < k - 1; ++i) {
        if (cur->m_pNext == nullptr) {
            return nullptr;
        }

        cur = cur->m_pNext;
    }

    ListNode *res = pListHead;
    while (cur->m_pNext != nullptr) {
        cur = cur->m_pNext;
        res = res->m_pNext;
    }

    return res;
}

void input() {
    int k;
    cin >> k;
    cout << "K is " << k << endl;

    vector<int> data;
    int input_data;
    while (cin >> input_data) {
        if (input_data == '\n') {
            break;
        }

        data.push_back(input_data);
    }

    cout << "Array: " << endl;
    for (auto item : data) {
        cout << item << "  ";
    }
    cout << endl;

    ListNode *head = build_list(data);
    ListNode *res = find_k_node(head, k);

    if (res == nullptr) {
        cout << "Can't find last " << k << "-th value" << endl;
    } else {
        cout << "Find last " << k << "-th value: " << res->m_value << endl;
    }
}

}  // FIND_K_NODE

#endif //CPP_WS_FIND_K_NODE_H_
