#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <fstream>
#include "graph.hpp"
using namespace std;

Graph::Graph(const string& filename) {

  ifstream infile;
  infile.open(filename); // Do this the preferred way after passing test cases

  // Add code to convert weighted, directed, and format into boolean values
  infile >> weighted >> directed >> format >> numVertices;

  if (format == "ListEdges" && weighted == "Unweighted") {

    int vert1, vert2;
    graphMatrix.resize(numVertices, vector<int>(numVertices));

    while (infile >> vert1 >> vert2) {
      graphMatrix[vert1][vert2] = 1;
      if (directed == "Undirected") {
        graphMatrix[vertt2][vert1] = 1;
      }
    }
  }
  else if (format == "ListEdges" && weighted == "Weighted") {

    int vert1, vert2, weight;
    graphMatrix.resize(numVertices, vector<int>(numVertices));

    while (infile >> vert1 >> vert2 >> weight) {
      graphMatrix[vert1][vert2] = weight;
      if (directed == "Undirected") {
        graphMatrix[vertt2][vert1] = weight;
      }
    }
  }
  else if (format == "AdjMatrix" && weighted == "Unweighted") {

    string rowString;
    char newline;
    vector<string> tempMatrix;
    int i, j;

    graphMatrix.resize(numVertices, vector<int>(numVertices));

    getline(infile, newline) // ignore newline leftover from infile >>

    while (getline(infile, rowString)) {
      tempMatrix.push_back(rowString);
    }

    for (i = 0; i < numVertices; i++) {

      rowString = tempMatrix[i];

      for (j = 0; j < rowString.size(); j++) {
        if (rowString[j] = 'T') {
          rowString[j] = 1;
        }
        else {
          rowString[j] = 0;
        }
        graphMatrix[i][j] = rowString[j];
      }
    }
  }
  else if (format == "AdjMatrix" && weighted == "Weighted") {
  }
  else if (format == "AdjList" && weighted == "Weighted") {
  }
  else
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
