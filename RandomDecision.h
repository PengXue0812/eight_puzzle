//
// Created by xue on 2022/11/27.
//

#ifndef EIGHT_PUZZLE_RANDOMDECISION_H
#define EIGHT_PUZZLE_RANDOMDECISION_H

#include "Solution.h"

class RandomDecision : public Solution {
    public:
    SIZE_T eightDigitalQues(const string &ini, const string &target) {
            bool isSolvabled = this->isSolvable(ini, target);
            if (!isSolvabled) {
                cout << "逆序数不同,该问题无解" << endl;
                return -1;
            }
            targetStr = target;
            len = sqrt(ini.length());
            vector<string> open;
            unordered_set<string> close;
            unordered_map<string, string> pre;
            open.emplace_back(ini);
            pre[ini] = "None";
            LARGE_INTEGER frequency;
            LARGE_INTEGER start;
            LARGE_INTEGER end;
            QueryPerformanceFrequency(&frequency);
            QueryPerformanceCounter(&start);
            while (!open.empty()) {
                int index = rand() % open.size();
                string n = open[index];
                open.erase(open.begin() + index);
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
                        open.emplace_back(str);
                        pre[str] = n;
                        count++;
                    }
                }
            }
            QueryPerformanceCounter(&end);
            pringtPath(pre, target);
            cout << "随机选择算法的搜索节点数为: " << count << endl;
            cout << "随机选择算法的搜索时间为: " << (end.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart << "ms" << endl;
            return -1;
        }
};


#endif //EIGHT_PUZZLE_RANDOMDECISION_H
