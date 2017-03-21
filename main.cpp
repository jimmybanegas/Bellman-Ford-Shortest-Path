#include "Test.h"
#include "Edge.h"
#include <iostream>
#include <limits>
using namespace std;

int INT_MAX = std::numeric_limits<int>::max();

vector<Edge> getEdges(int ** graph, int size)
{
    vector<Edge> edges;
    for (int i = 0; i <size; i++)
        for (int j = 0; j < size; j++)
            if(graph[i][j]!=-1)
            {
                Edge edge(i,j,graph[i][j]);
                edges.push_back(edge);
            }
    return edges;
}

int* getShortestPath(int** graph, int size, int origin)
{
    // V-> Number of vertices, E-> Number of edges
    int V = size;
    vector<Edge > edges = getEdges(graph,size);
    int E = edges.size();
    int dist[size];

     // Step 1: Initialize distances from src to all other vertices
     // as INFINITE
     // inicializamos el grafo. Ponemos distancias a INFINITO menos el nodo origen que
     // tiene distancia 0
    int * predecesor = new int[size];

      for (int i = 0; i < V; i++)
      {
            dist[i] = INT_MAX;
            predecesor[i] = NULL;
      }
    dist[origin] = 0;

    // relajamos cada arista del grafo tantas veces como número de nodos -1 haya en el grafo
    // Step 2: Relax all edges |V| - 1 times. A simple shortest
    // path from src to any other vertex can have at-most |V| - 1
    // edges
    for (int i = 1; i <= V-1; i++)
        for (int j = 0; j < E; j++)
        {
            int u = edges[j].source;
            int v = edges[j].destination;
            int weight = edges[j].weight;
            if (dist[u]!=INT_MAX && dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
                predecesor[v] = u;
            }
        }

   // comprobamos si hay ciclos negativo
   // Step 3: check for negative-weight cycles.  The above step
    // guarantees shortest distances if graph doesn't contain
    // negative weight cycle.  If we get a shorter path, then there
    // is a cycle.
    for (int i = 0; i < E; i++)
    {
        int u = edges[i].source;
        int v = edges[i].destination;
        int weight = edges[i].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
            printf("Graph contains negative weight cycle");
    }

    return predecesor;
}

int main ()
{
    test();
    return 0;
}
