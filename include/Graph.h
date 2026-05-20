#pragma once

#include <vector>
#include <cstddef>

template <typename T>
class Graph {
public:
    Graph() = default;
    ~Graph() = default;

    size_t addVertex(const T& data) {
        m_vertices.push_back(data);
        m_adjList.emplace_back(); 
        return m_vertices.size() - 1;
    }

    void addEdge(size_t from, size_t to) {
        m_adjList[from].push_back(to);
    }

    T& getVertexData(size_t index) {
        return m_vertices[index];
    }

    const T& getVertexData(size_t index) const {
        return m_vertices[index];
    }

    size_t getVertexCount() const {
        return m_vertices.size();
    }

    const std::vector<size_t>& getNeighbors(size_t index) const {
        return m_adjList[index];
    }

    void clear() {
        m_vertices.clear();
        m_adjList.clear();
    }

private:
    std::vector<T> m_vertices;                 
    std::vector<std::vector<size_t>> m_adjList; 

};