#pragma once

#include <vector>
#include <cstddef>

// Generic Template Graph using an Adjacency List representation
template <typename T>
class Graph {
public:
    Graph() = default;
    ~Graph() = default;

    // Adds a new vertex containing user data and returns its unique index
    size_t addVertex(const T& data) {
        m_vertices.push_back(data);
        m_adjList.emplace_back(); // Initialize an empty neighbor list for this vertex
        return m_vertices.size() - 1;
    }

    // Adds a directed edge from one vertex index to another
    void addEdge(size_t from, size_t to) {
        m_adjList[from].push_back(to);
    }

    // Returns a mutable reference to the data stored inside a vertex
    T& getVertexData(size_t index) {
        return m_vertices[index];
    }

    // Returns a read-only reference to the data stored inside a vertex
    const T& getVertexData(size_t index) const {
        return m_vertices[index];
    }

    // Returns the total number of registered vertices
    size_t getVertexCount() const {
        return m_vertices.size();
    }

    // Returns the list of adjacent vertex indices for a specific vertex
    const std::vector<size_t>& getNeighbors(size_t index) const {
        return m_adjList[index];
    }

    // Clears all vertices and connectivity maps from memory
    void clear() {
        m_vertices.clear();
        m_adjList.clear();
    }

private:
    std::vector<T> m_vertices;                 // Node payload storage
    std::vector<std::vector<size_t>> m_adjList; // Connectivity configuration
};