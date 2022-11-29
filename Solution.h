#ifndef EIGHT_PUZZLE_SOLUTION_H
#define EIGHT_PUZZLE_SOLUTION_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>
#include <unordered_set>
#include <windows.h>
#include <cmath>
#include<Psapi.h>

using namespace std;

class Solution {
protected:
    static string targetStr;
    int len;
    int count = 0;
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;

    inline void swapChr(string &child, int iniIdx, int childIdx) {//将iniidx下的0与childidx下的数字交换
        child[iniIdx] = child[childIdx];
        child[childIdx] = '0';
    }

    const vector<vector<int>> dirs = {{-1, 0},
                                      {1,  0},
                                      {0,  -1},
                                      {0,  1}};//上下左右

    void pringtPath(unordered_map<string, string> &pre, string path) {
        stack<string> s;
        while (path != "None") {
            s.emplace(path);
            path = pre[path];
        }
        int cnt = 0;
        while (++cnt && !s.empty()) {
            string str = s.top();
            s.pop();
            cout << "step" << cnt << ": " << endl;
            for (int i = 0; i < len * len; i++) {
                cout << str[i] << " ";
                if (i % len == len - 1) cout << endl;
            }
            cout << "-----------------" << endl;
        }
        cout << "共需要移动" << cnt - 1 << "步" << endl;
    }

    bool isSolvable(const string &ini, const string &target) {
        int inversions = 0;
        for (int i = 0; i < ini.length(); i++) {
            if (ini[i] == '0') continue;
            for (int j = i + 1; j < ini.length(); j++) {
                if (ini[j] == '0') continue;
                if (ini[i] > ini[j]) inversions++;
            }
        }
        for (int i = 0; i < target.length(); i++) {
            if (target[i] == '0') continue;
            for (int j = i + 1; j < target.length(); j++) {
                if (target[j] == '0') continue;
                if (target[i] > target[j]) inversions++;
            }
        }
        return inversions % 2 == 0;
    }

public:
    SIZE_T virtual eightDigitalQues(const string &ini, const string &target){
        return -1;
    }
};


#endif //EIGHT_PUZZLE_SOLUTION_H
