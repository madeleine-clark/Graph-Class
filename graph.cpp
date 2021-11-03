#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <fstream>
#include <sstream>
#include "graph.hpp"
using namespace std;

Graph::Graph(const string& filename) {

  ifstream infile;
  infile.open(filename); // Do this the preferred way after passing test cases

  string tempWeighted, tempDirected;

  infile >> tempWeighted >> tempDirected >> format >> numVert;

  weighted = (tempWeighted == "Weighted") ? true : false;
  directed = (tempDirected == "Directed") ? true : false;

  // cout << "So far so good" << endl; ==> good up until this point

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
    string newline;
    vector<string> tempMatrix;

    graphMatrix.resize(numVert, vector<int>(numVert));

    getline(infile, newline); // ignore newline leftover from infile >>

    while (getline(infile, rowString)) {
      tempMatrix.push_back(rowString);
    }

    for (size_t i = 0; i < numVert; i++) { // WHY SIZE_T ??
      rowString = tempMatrix[i];
      for (size_t j = 0; j < rowString.size(); j++) {
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
    string newline;
    vector<string> tempMatrix;

    graphMatrix.resize(numVert, vector<int>(numVert));

    getline(infile, newline); //ignore newline leftover from infile >>

    while (getline(infile, rowString)) {
      tempMatrix.push_back(rowString);
    }

    for (size_t i = 0; i < numVert; i++) {
      rowString = tempMatrix[i];
      for (size_t j = 0; j < rowString.size(); j++) {
        graphMatrix[i][j] = rowString[j];
        numEdges++;
        if(!(directed)) {
          graphMatrix[j][i] = rowString[j];
        }
      }
    }


  }
  else if (format == "AdjList" && !(weighted)) {

    string rowString;
    string newline;
    vector<string> tempMatrix;

    graphMatrix.resize(numVert, vector<int>(numVert));

    getline(infile, newline); // ignore newline leftover from infile >>

    while (getline(infile, rowString)) {
      tempMatrix.push_back(rowString);
    }

    int neighbor;

    for (size_t i = 0; i < numVert; i++) { // WHY SIZE_T ??
      rowString = tempMatrix[i];
      for (size_t j = 0; j < rowString.size(); j++) {
        neighbor = rowString.at(j);
        graphMatrix[i][neighbor] = 1;
        numEdges++;
        if(!(directed)) {
          graphMatrix[neighbor][i] = 1;
        }
      }
    }
  }
  else {

        graphMatrix.resize(numVert, vector<int>(numVert));

        string newline;
        getline(infile, newline); // ignore newline leftover from infile >>

        istringstream inSS;
        string rowString;

        unsigned neighbor;
        int weight;

        for (unsigned currVert = 0; currVert < numVert; currVert++) {

          getline(infile, rowString);

          inSS.clear();
          inSS.str(rowString);

          while (inSS >> neighbor >> weight){
            // cout << "Edge from " << currVert << " to " << neighbor << " with weight " << weight << endl;
            graphMatrix[currVert][neighbor] = weight;
            // cout << numEdges << endl;
            numEdges++;
            if(!(directed)) {
              graphMatrix[neighbor][currVert] = weight;
            }
          }
        }
  }
  makeAdjacencyList();
}

Graph::Graph(unsigned numVertices, const vector<pair<unsigned, unsigned>>& edges, bool isDirected) {

  directed = isDirected;
  numVert = numVertices;
  weighted = false;

  graphMatrix.resize(numVert, vector<int>(numVert));

  unsigned vert1, vert2;

  for (size_t i = 0; i < edges.size(); i++) {

    vert1 = edges[i].first;
    vert2 = edges[i].second;

    graphMatrix[vert1][vert2] = 1;

    numEdges++;

    if (!directed) {
      graphMatrix[vert2][vert1] = 1;
    }
  }

  makeAdjacencyList();

}

Graph::Graph(unsigned numVertices,const vector<tuple<unsigned, unsigned, int>>& edges, bool isDirected){

  directed = isDirected;
  numVert = numVertices;
  weighted = true;

  graphMatrix.resize(numVert, vector<int>(numVert));

  unsigned vert1, vert2;
  int weight;

  for (size_t i = 0; i < edges.size(); i++) {

    vert1 = get<0>(edges[i]);
    vert2 = get<1>(edges[i]);
    weight = get<2>(edges[i]);

    graphMatrix[vert1][vert2] = weight;
    numEdges++;

    if (!directed) {
      graphMatrix[vert2][vert1] = weight;
    }
  }

  makeAdjacencyList();
}

void Graph::makeAdjacencyList() {
  cout << "I'm being made!" << endl;
  graphList.resize(numVert);
  pair<unsigned, int> currNeighbor;

  for (size_t currRow; currRow < numVert; currRow++) {
    for (size_t currCol; currCol < numVert; currCol++) {
      if (graphMatrix[currRow][currCol] != 0) {
        currNeighbor.first = currCol;
        currNeighbor.second = graphMatrix[currRow][currCol];
        graphList[currRow].push_back(currNeighbor);
        }
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
  return graphList;
}

/*

// DO GRAPH ALGOS AFTER EVEYTHING ELSE IS WORKING

vector<unsigned> getBFSOrdering(unsigned start) const {
}

vector<unsigned> getDFSOrdering(unsigned start) const{
}

vector<vector<bool>> getTransitiveClosure() const{
}
*/
