#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <deque>
#include <queue>
using namespace std;

struct edge;

struct vertex{ //�������
	int id;
	vector<edge> incid; //������ ����, �� ���� ������� 
	vertex(){

	}
	vertex(int id){ //����� ������� 
		this->id = id;
	}
};

struct edge{ //�����
	int cost; // ���������
	vertex *v; //�������, � ������� ����������

	edge(){

	}
	
	edge(int c, vertex *vr){
		this->cost = c;
		this->v = vr;
	}
};

class graph{
	private:
		int size = 0; //���������� ���� � �����
		vector<bool> used; //i-��� ������� ����������, �������� �� �� i-��� ������� (��� ������)
	public:
	vector<vertex*> g; //������� � �����
	graph(int n){
		this->size = n; //�������� ������
		g.resize(n); //��������� ������  
		used.resize(n, false); 
		for (int i = 0; i < n; i++) //������ �������
			g[i] = new vertex(i);
	}
	graph(){

	}
	vertex* operator[](int); // ����������� �������� ���������� ������ (��� �������� �����)
	void clear_used(); //������� ������ used (����� ������, ��������)
	void dfs_rec(int, int); //����������� ���������� ������ � ������� 
	void dfs(int); // ������������� 
	void bfs(int); //����� � ������
};


vertex* graph::operator[](int k){ 
	if (k >= 0 && k < size) //���� � ����� � ���������� ��������
		return g[k]; //���������� �-��� �������
	return NULL; //����� ���
}

void graph::clear_used(){
	for (int i = 0; i < used.size(); i++) used[i] = false;
}

void graph::dfs_rec(int v, int cost){
	used[v] = true; //�������� ������� ��������� 
	cout << "DFS-recursive - Vertex: " <<  v << ", cost: " << cost << endl;
	for (int i = 0; i < g[v]->incid.size(); i++) //����� �� ������������ ��������
	if (!used[g[v]->incid[i].v->id]) //���� �� �������� 
		dfs_rec(g[v]->incid[i].v->id, g[v]->incid[i].cost); //���������� ���������� �� �������
}

void graph::bfs(int v){
	used[v] = true; //�������� ������� ��������� 
	queue<pair<int, int>> q; //������� �� ���, first - ����� �������, second - ���������
	q.push(make_pair(v, 0)); //������ � ������� �������
	while (!q.empty()){ //���� ������� �� ��������
		pair<int, int> z = q.front(); //���� �������
		cout << "BFS - Vertex: " << z.first << ", cost: " << z.second << endl;
		q.pop(); //������� ��� �� �������
		for (int i = 0; i < g[z.first]->incid.size(); i++){ // ����� �� ������������ ��������
			if (!used[g[z.first]->incid[i].v->id]){ // ���� �� ���� ��� 
				q.push(make_pair(g[z.first]->incid[i].v->id, g[z.first]->incid[i].cost)); //������ � �������
				used[g[z.first]->incid[i].v->id] = true; //�������� ����������
			}
		}
	}
}

void graph::dfs(int v){
	stack<pair<int, int>> s; //���� �� ���, first - ����� �������, second - ���������
	used[v] = true; //�������� ������� ��������� 
	s.push(make_pair(v, 0));  //��������� � ���� �������
	while (!s.empty()){ //���� ���� �� ��������
		pair<int, int> c = s.top(); //���� ������� �������
		for (int i = 0; i < g[c.first]->incid.size(); i++){ // ����� �� ������������ ��������
			if (!used[g[c.first]->incid[i].v->id]){// ���� �� ���� ��� 
				s.push(make_pair(g[c.first]->incid[i].v->id, g[c.first]->incid[i].cost)); //������ � ����
				used[g[c.first]->incid[i].v->id] = true; //�������� ���������� 
				cout << "DFS - Vertex: " << g[c.first]->incid[i].v->id << ", cost: " << g[c.first]->incid[i].cost << endl;
				break; //���������
			}
			else if(!s.empty()){ 
				s.pop(); //������� ������� ������� �����
			}
		}
	}
}

int main()
{
	freopen("input.txt", "r", stdin); //������ �� �����
	int n, m; //����������� ������� ��������������
	cin >> n >> m; 
	graph gr(max(n, m)); //������ ���� 
	for (int i = 0; i < n; i++)
	for (int j = 0; j < m; j++){
		int c; cin >> c; //������ ���������
		if (c != 0) //���� ���� �����
			gr[i]->incid.push_back(edge(c, gr[j])); //��������� ������� � ����
	}
	gr.dfs_rec(0, 0); //�������� ����� � ������� �� ������� � (�����������)
	gr.clear_used(); //������� ������ used
	gr.bfs(0); //����� � ������ �� ������� �
	gr.clear_used();
	gr.dfs(0); //����� � ������� ������������� �� ������� �
	gr.clear_used();
	return 0;
}

