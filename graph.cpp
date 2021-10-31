#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <fstream>
#include "graph.hpp"
using namespace std;

Graph::Graph(const string& filename) {

    ifstream ifs{filename};

    getline(ifs, weighted);
    getline(ifs, directed);
    getline(ifs, format);
    getline(if, numVertices);

    string currLine;
    while (getline(ifs, currLine)) {
      inputGraph.push_back(currLine);
    }
}

Graph::Graph(unsigned numVertices, const vector<pair<unsigned, unsigned>>& edges, bool isDirected){

}

Graph::Graph(unsigned numVertices,const vector<tuple<unsigned, unsigned, int>>& edges, bool isDirected){

}

bool Graph::isWeighted() const {
  return weighted;
}

bool Graph::isDirected() const {
  return directed;
}

unsigned Graph::getNumVertices() const {
  return numVertices;
}

unsigned Graph::getNumEdges() const {
  return numEdges;
}

vector<vector<int>> Graph::getAdjacencyMatrix() const {
}

vector<vector<pair<unsigned, int>>> Graph::getAdjacencyList() const {
}

vector<unsigned> getBFSOrdering(unsigned start) const;
vector<unsigned> getDFSOrdering(unsigned start) const;
