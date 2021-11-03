#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <fstream>
#include <sstream>
#include <stack>
#include <queue>
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
  makeAllBFSOrderings();
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
  makeAllBFSOrderings();

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
  makeAllBFSOrderings();
}

void Graph::makeAdjacencyList() {

  graphList.resize(numVert);

  for (size_t currRow = 0; currRow < numVert; currRow++) {

    for (size_t currCol = 0; currCol < numVert; currCol++) {
      if (graphMatrix[currRow][currCol] != 0) {
        graphList[currRow].push_back(make_pair(currCol, graphMatrix[currRow][currCol]));
      }
      }
    }
}

void Graph::makeAllBFSOrderings() { // FINISH

  for (size_t startVert = 0; startVert < numVert; startVert++) {

    vector<bool> discovered(numVert, false);
    discovered[startVert] = true;

    vector<unsigned> bfs;
    unsigned currVert;

    queue<unsigned> q;
    q.push(startVert);

    while (!q.empty()) {

      currVert = q.front();
      q.pop();

      bfs.push_back(currVert); // Process the current vertice

      for (auto& neighbor : graphList[currVert]) {
        if (!discovered[neighbor.first]) {
          discovered[neighbor.first] = true;
          q.push(neighbor.first);
        }
      }
    }
  }
}

void Graph::makeAllDFSOrderings() { //FINISH

}

void Graph::makeTransitiveClosure() { //FINISH

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

// HOW CAN THIS BE CONST IF IT TAKES IN START?
// PERFORM BFS FOR EVERY START NODE IN HELPER FUNCTION??
vector<unsigned> Graph::getBFSOrdering(unsigned start) const {
  return allBfs.at(start);
}

vector<unsigned> Graph::getDFSOrdering(unsigned start) const {
  return allDfs.at(start);
}

vector<vector<bool>> Graph::getTransitiveClosure() const{
  return transitiveClosure;
}
