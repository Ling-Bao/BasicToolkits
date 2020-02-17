/**
 * Copyright (c) {2020}-present, DiDi, Inc.
 * All rights reserved.
 *
 *   File: {map.h}
 *   Author: {Baoling}
 *   Email: {baoling@didiglobal.com}
 *   Group: Visual Computing Group at DiDi
 *   Created: {2020-01-19}
 *   Description: {Todo: describe this file's function}
 */


#ifndef CPP_WS_MAP_H_
#define CPP_WS_MAP_H_

#include <vector>
#include <map>
#include <set>
#include <iostream>

using namespace std;

namespace STL_MAP {

void input() {
    map<int, set<int>> val_map;

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (val_map.count(i)) {
                val_map[i].insert(j);
            } else {
                set<int> tmp {j};
                val_map[i] = tmp;
            }
        }
    }

    for (auto elem_map : val_map) {
        for (auto elem_set : elem_map.second ) {
            cout << elem_set << " ";
        }
        cout << endl;
    }
}

}  // STL_MAP

#endif //CPP_WS_MAP_H_
