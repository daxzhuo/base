

#include <iostream>
#include <vector>
#include <algorithm>

class Edge
{
public:
	Edge(int s, int d, int w):src(s), dest(d), weight(w) {}

	int src, dest, weight;
};

class Graph {
public:
	Graph(int v) : ss(v){
		for (int i = 0; i < v; ++i) {
			ss[i] = i;
		}
	}
	int find(int i);
	std::vector<Edge> MstKruskal();
	void Union(int u, int v);
	void addEdge(int u, int v, int weight);
private:

	std::vector<Edge> edge;

	std::vector<int> ss;


};

void Graph::addEdge(int u, int v, int w) {
	edge.emplace_back(u, v, w);
}

int Graph::find(int i) {
	// path compress
	if (i != ss[i])
		ss[i] = find(ss[i]);
	return ss[i];
}

std::vector<Edge> Graph::MstKruskal() {
	std::vector<Edge> t;
	
	
	std::sort(edge.begin(), edge.end(),
						[](Edge& lhs, Edge& rhs) { return lhs.weight < rhs.weight;});

	for (auto& e : edge) {
		if (find(e.src) != find(e.dest)) {
			t.push_back(e);
			Union(e.src, e.dest);
		}
	}

	return t;

}

// union tree u and tree v
void Graph::Union(int u, int v) {
	int uroot = find(u);
	int vroot = find(v);
	ss[vroot] = uroot;
}

int main() {

  Graph graph(11);

  // add edge 0-1
  graph.addEdge(0, 1, 4);
  graph.addEdge(1, 2, 8);
  graph.addEdge(2, 3, 7);
  graph.addEdge(3, 4, 9);
  graph.addEdge(4, 5, 10);
  graph.addEdge(5, 6, 2);
  graph.addEdge(6, 7, 1);
  graph.addEdge(7, 8, 7);
  graph.addEdge(2, 8, 2);
  graph.addEdge(6, 8, 6);
  graph.addEdge(2, 5, 4);


  auto result = graph.MstKruskal();
  for (auto& e:result)
  	std::cout << e.src << "-" << e.dest << std::endl;
}