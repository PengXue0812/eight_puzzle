#ifndef EIGHT_PUZZLE_A_STAR_H
#define EIGHT_PUZZLE_A_STAR_H

#include "Solution.h"

class A_Star : public Solution {
private:
    struct state {
        string str;
        int depth;

        state(string s, int d) : str(s), depth(d) {}

        bool operator<(const state &s) const {//看有几个点不在正确位置
            int cnt1 = 0, cnt2 = 0;
            for (int i = 0; i < 9; i++) {
                if (str[i] == targetStr[i]) cnt1++;
                if (s.str[i] == targetStr[i]) cnt2++;
            }
            return cnt1 + this->depth < cnt2 + s.depth;
        }
    };

public:
    SIZE_T eightDigitalQues(const string &ini, const string &target) {
        bool isSolvabled = this->isSolvable(ini, target);
        if (!isSolvabled) {
            cout << "逆序数不同,该问题无解" << endl;
            return -1;
        }
        targetStr = target;
        len = sqrt(ini.length());
        priority_queue<state> open;
        unordered_set<string> close;
        unordered_map<string, string> pre;
        open.emplace(ini, 0);
        pre[ini] = "None";

        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);
        while (!open.empty()) {
            string n = open.top().str;
            int depth = open.top().depth;
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
                    state childState(n, depth + 1);
                    swapChr(childState.str, iniInd, childInd);
                    if (close.count(childState.str)) {
                        continue;
                    }
                    open.emplace(childState);
                    pre[childState.str] = n;
                    count++;
                }
            }
        }
        QueryPerformanceCounter(&end);
        pringtPath(pre, target);
        cout << "A*算法的搜索节点数为: " << count << endl;
        cout << "A*算法的搜索时间为: " << (end.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart << "ms" << endl;
        HANDLE hProcess = GetCurrentProcess();
        PROCESS_MEMORY_COUNTERS pmc;
        GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc));
        SIZE_T virtualMemUsedByMe = pmc.WorkingSetSize;
        return virtualMemUsedByMe;
    }
};


#endif //EIGHT_PUZZLE_A_STAR_H
