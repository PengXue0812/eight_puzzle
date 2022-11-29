//
// Created by xue on 2022/11/27.
//
# include "BFS.h"
# include "A_Star.h"
# include "A_Star2.h"
# include "DFS.h"
# include "RandomDecision.h"

string Solution::targetStr;

int main() {
    printf("请输入1-5 选择算法：\n");
    printf("1.BFS\n2.A_Star\n3.A_Star2\n4.DFS\n5.RandomDecision\n");

    int choice;
    cin >> choice;
    string ini, target;
    cout << "请输入初始状态(不需要带空格)：" << endl;
    cin >> ini;
    cout << "请输入目标状态(不需要带空格)：" << endl;
    cin >> target;
    Solution *S;
    switch (choice) {
        case 1:
            S = new BFS();
            break;
        case 2:
            S = new A_Star();
            break;
        case 3:
            S = new A_Star2();
            break;
        case 4:
            S = new DFS();
            break;
        case 5:
            S = new RandomDecision();
            break;
        default:
            printf("输入错误！\n");
            return 0;
    }
    SIZE_T count = S->eightDigitalQues(ini, target);
    if (count == -1) {
        return 0;
    }

    HANDLE hProcess = GetCurrentProcess();
    PROCESS_MEMORY_COUNTERS pmc;
    GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc));
    SIZE_T virtualMemUsedByMe = pmc.WorkingSetSize;
    count += virtualMemUsedByMe;
    cout << "内存占用为: " << count / 1024.0 / 1024.0 / 1024.0 << "GB" << endl;
    return 0;
}