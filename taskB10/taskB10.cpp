#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <deque>
using namespace std;

struct edge;

struct vertex{
	int id;
	vector<edge> incid;
	vertex(){

	}
	vertex(int id){
		this->id = id;
	}
};

struct edge{
	int cost;
	vertex *v;

	edge(){

	}
	
	edge(int c, vertex *vr){
		this->cost = c;
		this->v = vr;
	}
};

class graph{
	private:
		int size = 0;
	public:
	vector<vertex*> g;
	graph(int n){
		this->size = n;
		g.resize(n);
	}
	vertex* operator[](int);
};

vertex* graph::operator[](int k){
	if (k >= 0 && k < size)

		return g[k];
	return NULL;
}

int main()
{
	graph *gr = new graph(10);
	auto b = *gr;
	auto z = b[8];
	int n = 0;
	return 0;
}

