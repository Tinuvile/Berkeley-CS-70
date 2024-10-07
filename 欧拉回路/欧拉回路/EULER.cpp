#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

class Graph {
public:
	int V;  //������
	vector<vector<int>> adj;  //�ڽӱ�

	//���캯�������ܶ�����������ʼ���ڽӱ�Ĵ�С
	Graph(int V) {
		this->V = V;
		adj.resize(V);
	}

	//��ӴӶ���u��v�������
	void addEdge(int u, int v) {
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	//ͨ�������������DFS���ҴӶ���s������һ������·��
	vector<int> findTour(int s);
	//����Ӷ���s����Ѱ��ŷ����·
	void Euler(int s);
	//�ϲ�����·������������·����ƴ��
	void splice(vector<int>& T, vector<int>& T1);
};

vector<int>Graph::findTour(int s) {
	vector<int> tour;  //����·��
	stack<int> stk;  //��������Ľڵ�
	vector<bool> visitedEdges(V, false);  //��¼�ѷ��ʵı�
	int currentVertex = s;  //��¼��ǰ�ڵ�

	stk.push(currentVertex);

	while (!stk.empty()) {
		if (!adj[currentVertex].empty()) {
			//ѡ��δ���ʵ�
			int next = adj[currentVertex].back();
			adj[currentVertex].pop_back();
			//���ڽӱ�����
			adj[next].erase(remove(adj[next].begin(), adj[next].end(), currentVertex), adj[next].end());
			stk.push(currentVertex);
			currentVertex = next;
		}
		else {
			//��ǰ�ڵ�δ���ʵ�
			tour.push_back(currentVertex);
			currentVertex = stk.top();
			stk.pop();
		}
	}

	return tour;
}

void Graph::splice(vector<int>& T,vector<int>& T1){
	//�˴�δʾ����ʵ�������߼����
	for (int v : T) {
		cout << v << " ";
	}
	cout << "->";
	for (int v : T1) {
		cout << v << " ";
	}
	cout << endl;
}

void Graph::Euler(int s) {
	vector<int> T = findTour(s);
	//����T�еıߴ�����ͼ(Gi)
	//������Կ�չ�߼�������T��ص���ͼ
	cout << "Tour Found: " << endl;
	for (int val : T) {
		cout << val << " ";
	}
	cout << endl;
}

int main() {
	Graph g(5);
	g.addEdge(1, 2);
	g.addEdge(2, 0);
	g.addEdge(1, 3);
	g.addEdge(3, 4);
	g.addEdge(4, 1);

	g.Euler(0);
}