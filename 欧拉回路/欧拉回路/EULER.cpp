#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

class Graph {
public:
	int V;  //顶点数
	vector<vector<int>> adj;  //邻接表

	//构造函数，接受顶点数量并初始化邻接表的大小
	Graph(int V) {
		this->V = V;
		adj.resize(V);
	}

	//添加从顶点u到v的无向边
	void addEdge(int u, int v) {
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	//通过深度优先搜索DFS查找从顶点s出发的一条游历路径
	vector<int> findTour(int s);
	//处理从顶点s出发寻找欧拉回路
	void Euler(int s);
	//合并两条路径，处理两条路径的拼接
	void splice(vector<int>& T, vector<int>& T1);
};

vector<int>Graph::findTour(int s) {
	vector<int> tour;  //储存路径
	stack<int> stk;  //储存遍历的节点
	vector<bool> visitedEdges(V, false);  //记录已访问的边
	int currentVertex = s;  //记录当前节点

	stk.push(currentVertex);

	while (!stk.empty()) {
		if (!adj[currentVertex].empty()) {
			//选择未访问的
			int next = adj[currentVertex].back();
			adj[currentVertex].pop_back();
			//从邻接表中移
			adj[next].erase(remove(adj[next].begin(), adj[next].end(), currentVertex), adj[next].end());
			stk.push(currentVertex);
			currentVertex = next;
		}
		else {
			//当前节点未访问的
			tour.push_back(currentVertex);
			currentVertex = stk.top();
			stk.pop();
		}
	}

	return tour;
}

void Graph::splice(vector<int>& T,vector<int>& T1){
	//此处未示例，实际需结合逻辑输出
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
	//根据T中的边创建子图(Gi)
	//这里可以开展逻辑处理，与T相关的子图
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