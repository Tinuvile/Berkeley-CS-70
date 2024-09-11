#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int N = 4; //�������ĸ��������ĸ���ѡ��
int Jobs[][4] = { {1,2,3,4},{1,4,3,2},{1,3,2,4},{1,2,3,4} };
int Candidates[][4] = { {1,3,2,4},{4,3,2,1},{2,3,1,4},{3,4,2,1} };

int preferenceRank[N][N];

vector<int> jobMatch(N, -1); // ��ʼ��ƥ��Ϊ��

//��ʼ��ƫ������
void initPreferenceRank()
{
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			preferenceRank[i][Candidates[i][j] - 1] = j;
		}
	}
}

int StableMatching() {
    vector<bool> freeJobs(N, true); // ���й����������ɵ�
    vector<int> jobNextProposal(N, 0); // ÿ��������һ������ĺ�ѡ��

    int freeCount = N; // ��ʼ���ɹ�������

    while (freeCount > 0) {
        int job;
        for (job = 0; job < N; ++job) {
            if (freeJobs[job]) {
                break;
            }
        }

        // ѡ��ǰ���ɹ�����һ������ĺ�ѡ��
        int candidateIndex = jobNextProposal[job];
        int candidate = Jobs[job][candidateIndex] - 1;

        // ����ƥ��
        if (jobMatch[candidate] == -1) {
            // �����ѡ��δƥ�䣬��������
            jobMatch[candidate] = job;
            freeJobs[job] = false;
            freeCount--;
        }
        else {
            // ��ѡ���Ѿ�ƥ�䣬�ж��Ƿ����������
            int currentJob = jobMatch[candidate];
            if (preferenceRank[candidate][job] < preferenceRank[candidate][currentJob]) {
                // �¹������ܻ�ӭ���滻
                jobMatch[candidate] = job;
                freeJobs[currentJob] = true; // �ͷžɵĹ���
                freeJobs[job] = false; // �������������ƥ����
            }
        }

        // ������һ������ĺ�ѡ��
        jobNextProposal[job]++;
    }

    return 0;
}

int main() {
    // ��ʼ��ƫ������
    initPreferenceRank();
    StableMatching();

    // ��ӡƥ����
    cout << "Stable Matchings between Jobs and Candidates:\n";
    for (int i = 0; i < N; ++i) {
        cout << "Candidate " << (i + 1) << " is matched with Job " << (jobMatch[i] + 1) << "\n";
    }

    return 0;
}