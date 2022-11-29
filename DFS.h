//
// Created by xue on 2022/11/4.
//

#ifndef EIGHT_PUZZLE_DFS_H
#define EIGHT_PUZZLE_DFS_H

#include "Solution.h"
#include <stack>

class DFS : public Solution {
public:
    SIZE_T eightDigitalQues(const string &ini, const string &target) {
        bool isSolvabled = this->isSolvable(ini, target);
        if (!isSolvabled) {
            cout << "逆序数不同,该问题无解" << endl;
            return -1;
        }
        targetStr = target;
        len = sqrt(ini.length());
        stack<string> open;
        unordered_set<string> close;
        unordered_map<string, string> pre;
        open.emplace(ini, 0);
        pre[ini] = "None";
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);
        while (!open.empty()) {
            string n = open.top();
            open.pop();
            close.emplace(n);
            if (n == target) {
                break;
            }
            int iniInd = n.find('0');
            int x = iniInd / len, y = iniInd % len;
            for (const auto &dir: dirs) {
                int newX = x + dir[0], newY = y + dir[1];
                if (newX >= 0 && newX <= len - 1 && newY >= 0 && newY <= len - 1) {
                    int childInd = newX * 3 + newY;
                    string str = n;
                    swapChr(str, iniInd, childInd);
                    if (close.count(str)) {
                        continue;
                    }
                    open.emplace(str);
                    pre[str] = n;
                    count++;
                }
            }
        }
        QueryPerformanceCounter(&end);
        pringtPath(pre, target);
        cout << "DFS算法的搜索节点数为: " << count << endl;
        cout << "DFS算法运行时间为：" << (end.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart << "ms" << endl;
        HANDLE hProcess = GetCurrentProcess();
        PROCESS_MEMORY_COUNTERS pmc;
        GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc));
        SIZE_T virtualMemUsedByMe = pmc.WorkingSetSize;
        return virtualMemUsedByMe;
    }
};


#endif //EIGHT_PUZZLE_DFS_H
