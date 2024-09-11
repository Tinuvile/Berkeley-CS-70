#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int N = 4; //假设有四个工作和四个候选者
int Jobs[][4] = { {1,2,3,4},{1,4,3,2},{1,3,2,4},{1,2,3,4} };
int Candidates[][4] = { {1,3,2,4},{4,3,2,1},{2,3,1,4},{3,4,2,1} };

int preferenceRank[N][N];

vector<int> jobMatch(N, -1); // 初始化匹配为空

//初始化偏好排名
void initPreferenceRank()
{
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			preferenceRank[i][Candidates[i][j] - 1] = j;
		}
	}
}

int StableMatching() {
    vector<bool> freeJobs(N, true); // 所有工作都是自由的
    vector<int> jobNextProposal(N, 0); // 每个工作下一个提议的候选者

    int freeCount = N; // 初始自由工作数量

    while (freeCount > 0) {
        int job;
        for (job = 0; job < N; ++job) {
            if (freeJobs[job]) {
                break;
            }
        }

        // 选择当前自由工作下一个提议的候选者
        int candidateIndex = jobNextProposal[job];
        int candidate = Jobs[job][candidateIndex] - 1;

        // 尝试匹配
        if (jobMatch[candidate] == -1) {
            // 如果候选者未匹配，接受提议
            jobMatch[candidate] = job;
            freeJobs[job] = false;
            freeCount--;
        }
        else {
            // 候选者已经匹配，判断是否接受新提议
            int currentJob = jobMatch[candidate];
            if (preferenceRank[candidate][job] < preferenceRank[candidate][currentJob]) {
                // 新工作更受欢迎，替换
                jobMatch[candidate] = job;
                freeJobs[currentJob] = true; // 释放旧的工作
                freeJobs[job] = false; // 现在这个工作被匹配了
            }
        }

        // 更新下一个提议的候选者
        jobNextProposal[job]++;
    }

    return 0;
}

int main() {
    // 初始化偏好排名
    initPreferenceRank();
    StableMatching();

    // 打印匹配结果
    cout << "Stable Matchings between Jobs and Candidates:\n";
    for (int i = 0; i < N; ++i) {
        cout << "Candidate " << (i + 1) << " is matched with Job " << (jobMatch[i] + 1) << "\n";
    }

    return 0;
}