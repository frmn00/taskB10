#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <deque>
#include <queue>
using namespace std;

struct edge;

struct vertex{ //вершина
	int id;
	vector<edge> incid; //список ребёр, из этой вершины 
	vertex(){

	}
	vertex(int id){ //номер вершины 
		this->id = id;
	}
};

struct edge{ //ребро
	int cost; // стоимость
	vertex *v; //вершина, в которую напревлены

	edge(){

	}
	
	edge(int c, vertex *vr){
		this->cost = c;
		this->v = vr;
	}
};

class graph{
	private:
		int size = 0; //количество рёбер в графе
		vector<bool> used; //i-тый элемент обозначает, посетили ли мы i-тую вершину (при обходе)
	public:
	vector<vertex*> g; //вершины в графе
	graph(int n){
		this->size = n; //изменяем размер
		g.resize(n); //расширяем вектор  
		used.resize(n, false); 
		for (int i = 0; i < n; i++) //создаём вершины
			g[i] = new vertex(i);
	}
	graph(){

	}
	vertex* operator[](int); // перегуженый оператор квадратные скобки (для удобства далее)
	void clear_used(); //очищает массив used (после обхода, например)
	void dfs_rec(int, int); //рекурсивная реализация поиска в глубину 
	void dfs(int); // нерекурсивная 
	void bfs(int); //поиск в ширину
};


vertex* graph::operator[](int k){ 
	if (k >= 0 && k < size) //если к лежит в допустимых пределах
		return g[k]; //возвращает к-тую вершину
	return NULL; //иначе нул
}

void graph::clear_used(){
	for (int i = 0; i < used.size(); i++) used[i] = false;
}

void graph::dfs_rec(int v, int cost){
	used[v] = true; //помечаем вершину посёщенной 
	cout << "DFS-recursive - Vertex: " <<  v << ", cost: " << cost << endl;
	for (int i = 0; i < g[v]->incid.size(); i++) //бежим по инциндентным вершинам
	if (!used[g[v]->incid[i].v->id]) //если не посещали 
		dfs_rec(g[v]->incid[i].v->id, g[v]->incid[i].cost); //рекурсивно вызываемся из вершины
}

void graph::bfs(int v){
	used[v] = true; //помечаем вершину посёщенной 
	queue<pair<int, int>> q; //очередь из пар, first - номер вершины, second - стоимость
	q.push(make_pair(v, 0)); //кидаем в очередь вершину
	while (!q.empty()){ //пока очередь не опустеет
		pair<int, int> z = q.front(); //берёи элемент
		cout << "BFS - Vertex: " << z.first << ", cost: " << z.second << endl;
		q.pop(); //удаляем его из очереди
		for (int i = 0; i < g[z.first]->incid.size(); i++){ // бежим по инциндентным вершинам
			if (!used[g[z.first]->incid[i].v->id]){ // если не были там 
				q.push(make_pair(g[z.first]->incid[i].v->id, g[z.first]->incid[i].cost)); //кидаем в очередь
				used[g[z.first]->incid[i].v->id] = true; //помечаем посещённой
			}
		}
	}
}

void graph::dfs(int v){
	stack<pair<int, int>> s; //стек из пар, first - номер вершины, second - стоимость
	used[v] = true; //помечаем вершину посёщенной 
	s.push(make_pair(v, 0));  //добавляем в стек вершину
	while (!s.empty()){ //пока стек не опустеет
		pair<int, int> c = s.top(); //берём верхний элемент
		for (int i = 0; i < g[c.first]->incid.size(); i++){ // бежим по инциндентным вершинам
			if (!used[g[c.first]->incid[i].v->id]){// если не были там 
				s.push(make_pair(g[c.first]->incid[i].v->id, g[c.first]->incid[i].cost)); //видаем в стек
				used[g[c.first]->incid[i].v->id] = true; //помечаем посещённой 
				cout << "DFS - Vertex: " << g[c.first]->incid[i].v->id << ", cost: " << g[c.first]->incid[i].cost << endl;
				break; //брякаемся
			}
			else if(!s.empty()){ 
				s.pop(); //удаляем верхний элемент стека
			}
		}
	}
}

int main()
{
	freopen("input.txt", "r", stdin); //читаем из файла
	int n, m; //размерности матрицы инциндентности
	cin >> n >> m; 
	graph gr(max(n, m)); //создаём граф 
	for (int i = 0; i < n; i++)
	for (int j = 0; j < m; j++){
		int c; cin >> c; //читаем стоимость
		if (c != 0) //если есть пусть
			gr[i]->incid.push_back(edge(c, gr[j])); //добавляем вершину и путь
	}
	gr.dfs_rec(0, 0); //вызываем поиск в глубину из вершины а (рекурсивный)
	gr.clear_used(); //очищаем массив used
	gr.bfs(0); //поиск в ширину из вершины а
	gr.clear_used();
	gr.dfs(0); //поиск в глубину нерекурсивный из вершины а
	gr.clear_used();
	return 0;
}

