#pragma once

#include <vector>
#include <functional>
#include <unordered_map>

#include "PriorityQueue.h"

#define INF 0x3f3f3f3f

template <class Vertex>
class Graph
{
public:
	using vPair		= std::pair<Vertex, int>;
	using PathTo	= std::pair<int, Vertex>;
	using Paths		= std::unordered_map<Vertex, int>;
	using Adjective	= std::vector<vPair>;
	using HashTable = std::unordered_map<Vertex, Adjective>;

	Graph();
	Graph(const std::initializer_list<std::pair<Vertex, vPair>>& lst);

	void append(const Vertex& toVert, const vPair& newVert);
	Paths shortestPath(const Vertex& from) const;

private:
	HashTable m_adj;
	size_t m_size;
};

template<class Vertex>
Graph<Vertex>::Graph()
{
	m_size = 0;
}

template<class Vertex>
Graph<Vertex>::Graph(const std::initializer_list<std::pair<Vertex, vPair>>& lst)
{
	m_size = 0;
	for (const std::pair<Vertex, vPair>& p : lst) {
		append(p.first, p.second);
	}
}

template<class Vertex>
void Graph<Vertex>::append(const Vertex& toVert, const vPair& newVert)
{
	auto linked = m_adj.find(toVert);
	if (linked != m_adj.end()) {
		linked->second.push_back(newVert);
	}
	else {
		m_adj.insert({ toVert, { newVert } });
		m_size++;
	}

	linked = m_adj.find(newVert.first);
	if (linked != m_adj.end()) {
		linked->second.push_back({ toVert, newVert.second });
	}
	else {
		m_adj.insert({ newVert.first, { { toVert, newVert.second } } });
		m_size++;
	}
}

template<class Vertex>
typename Graph<Vertex>::Paths Graph<Vertex>::shortestPath(const Vertex& from) const
{
	PriorityQueue<PathTo, std::greater<PathTo>> pq;
	Paths paths;

	for (const std::pair<Vertex, Adjective>& p : m_adj) {
		paths.insert({ p.first, p.first == from ? 0 : INF });
	}

	pq.push({ 0, from });

	while (pq.size()) {
		Vertex u = pq.pop().second;
		auto it = m_adj.find(u);
		if (it == m_adj.end()) break;
		for (const vPair& p : it->second) {
			Vertex v = p.first;
			int weight = p.second;

			if (paths[v] > paths[u] + weight) {
				paths[v] = paths[u] + weight;
				pq.push({ paths[v], v });
			}
		}
	}

	return paths;
}
