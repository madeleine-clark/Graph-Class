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

  string tempWeighted, tempDirected;

  infile >> tempWeighted >> tempDirected >> format >> numVert;

  weighted = (tempWeighted == "Weighted") ? true : false;
  directed = (tempDirected == "Directed") ? true : false;

  if (format == "ListEdges" && !(weighted)) {

    int vert1, vert2;
    graphMatrix.resize(numVert, vector<int>(numVert));

    while (infile >> vert1 >> vert2) {
      graphMatrix[vert1][vert2] = 1;
      numEdges++;
      if (!(directed)) {
        graphMatrix[vert2][vert1] = 1;
      }
    }
  }
  else if (format == "ListEdges" && weighted) {

    int vert1, vert2, weight;
    graphMatrix.resize(numVert, vector<int>(numVert));

    while (infile >> vert1 >> vert2 >> weight) {
      graphMatrix[vert1][vert2] = weight;
      numEdges++;
      if (!(directed)) {
        graphMatrix[vert2][vert1] = weight;
      }
    }
  }
  else if (format == "AdjMatrix" && !(weighted)) {

    string rowString;
    char newline;
    vector<string> tempMatrix;

    graphMatrix.resize(numVert, vector<int>(numVert));

    getline(infile, newline); // ignore newline leftover from infile >>

    while (getline(infile, rowString)) {
      tempMatrix.push_back(rowString);
    }

    for (int i = 0; i < numVert; i++) {
      rowString = tempMatrix[i];
      for (int j = 0; j < rowString.size(); j++) {
        graphMatrix[i][j] = (rowString[j] == 'T') ? 1 : 0;
        numEdges++;
        if(!(directed)) {
          graphMatrix[j][i] = (rowString[j] == 'T') ? 1 : 0;
        }
      }
    }
  }
  else if (format == "AdjMatrix" && weighted) {

    string rowString;
    char newline;
    vector<string> temoMatrix;

    graphMatrix.resize(numVert, vector<int>(numVert));

    getline(infile, newline); //ignore newline leftover from infile >>

    while (getline(infile, rowString)) {
      tempMatrix.push_back(rowString);
    }

    for (int i = 0; i < numVert; i++) {
      rowString = tempMatrix[i];
      for (int j = 0; j < rowString.size(); j++) {
        graphMatrix[i][j] = rowString[j];
        numEdges++;
        if(!(directed)) {
          graphMatrix[j][i] = rowString[j];
        }
      }
    }


  }
  else if (format == "AdjList" && !(weighted)) {
  }
  else {

  }
}

Graph::Graph(unsigned numVertices, const vector<pair<unsigned, unsigned>>& edges, bool isDirected) {

  directed = isDirected;
  numVert = numVertices;
  weighted = false;

  graphMatrix.resize(numVert, vector<int>(numVert));

  unsigned vert1, vert2;

  for (int i = 0; i < edges.size(); i++) {

    vert1 = edges[i].first;
    vert2 = edges[i].second;

    graphMatrix[vert1][vert2] = 1;

    numEdges++;

    if (!directed) {
      graphMatrix[vert2][vert1] = 1;
    }
  }

}

Graph::Graph(unsigned numVertices,const vector<tuple<unsigned, unsigned, int>>& edges, bool isDirected){

  directed = isDirected;
  numVert = numVertices;
  weighted = true;

  graphMatrix.resize(numVert, vector<int>(numVert));

  unsigned vert1, vert2;
  int weight;

  for (int i = 0; i < edges.size(); i++) {

    vert1 = get<0>(edges);
    vert2 = get<1>(edges);
    weight = get<2>(edges);

    graphMatrix[vert1][vert2] = weight;

    numEdges++;

    if (!directed) {
      graphMatrix[vert2][vert1] = weight;
    }
  }


}

bool Graph::isWeighted() const {
  return weighted;
}

bool Graph::isDirected() const {
  return directed;
}

unsigned Graph::getNumVertices() const {
  return numVert;
}

unsigned Graph::getNumEdges() const {
  return numEdges;
}

vector<vector<int>> Graph::getAdjacencyMatrix() const {
  return graphMatrix;
}

vector<vector<pair<unsigned, int>>> Graph::getAdjacencyList() const {

}

// DO GRAPH ALGOS AFTER EVEYTHING ELSE IS WORKING
vector<unsigned> getBFSOrdering(unsigned start) const {
}

vector<unsigned> getDFSOrdering(unsigned start) const{
}

vector<vector<bool>> getTransitiveClosure() const{
}