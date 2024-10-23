/*
  Experiment 20
  Graph
  25 Athul Anoop
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct Graph {
  int num_vertices;
  int adj_matrix[MAX_VERTICES][MAX_VERTICES]; // adjacency matrix
  int adj_list[MAX_VERTICES][MAX_VERTICES];   // adjacency list
  int list_size[MAX_VERTICES];                // size of each adjacency list
} Graph;

void initialize_graph(Graph *graph, int vertices);
void add_edge(Graph *graph, int u, int v);
void display_adjacency_list(Graph *graph);
void display_adjacency_matrix(Graph *graph);
void dfs_recursive(Graph *graph, int vertex, bool visited[]);
void dfs(Graph *graph, int start_vertex);
void bfs(Graph *graph, int start_vertex);
void display_menu();
void handle_choice(Graph *graph);

int main() {
  printf("Number of vertices: ");
  int num_vertices;
  scanf("%d", &num_vertices);
  Graph graph;
  initialize_graph(&graph, num_vertices);

  display_menu();

  // main loop
  while (1) {
    handle_choice(&graph);
  }

  return 0;
}

// function definitions

// function to initialize the graph
void initialize_graph(Graph *graph, int vertices) {
  graph->num_vertices = vertices;

  // initialize adjacency matrix and list
  for (int i = 0; i < vertices; i++) {
    graph->list_size[i] = 0;
    for (int j = 0; j < vertices; j++) {
      graph->adj_matrix[i][j] = 0; // no edges initially
      graph->adj_list[i][j] = -1;  // initialize adjacency list
    }
  }
}

// function to add an edge between u and v
void add_edge(Graph *graph, int u, int v) {
  graph->adj_matrix[u][v] = 1;
  graph->adj_matrix[v][u] = 1; // undirected graph

  // adjacency list representation
  graph->adj_list[u][graph->list_size[u]++] = v;
  graph->adj_list[v][graph->list_size[v]++] = u; // undirected graph
}

// function to display the adjacency list
void display_adjacency_list(Graph *graph) {
  printf("adjacency list:\n");
  for (int i = 0; i < graph->num_vertices; i++) {
    printf("%d: ", i);
    for (int j = 0; j < graph->list_size[i]; j++) {
      printf("%d ", graph->adj_list[i][j]);
    }
    printf("\n");
  }
}

// function to display the adjacency matrix
void display_adjacency_matrix(Graph *graph) {
  printf("\nadjacency matrix:\n");
  for (int i = 0; i < graph->num_vertices; i++) {
    for (int j = 0; j < graph->num_vertices; j++) {
      printf("%d ", graph->adj_matrix[i][j]);
    }
    printf("\n");
  }
}

// recursive helper function for dfs
void dfs_recursive(Graph *graph, int vertex, bool visited[]) {
  visited[vertex] = true; // mark vertex as visited
  printf("%d ", vertex);

  // visit all adjacent unvisited vertices
  for (int i = 0; i < graph->list_size[vertex]; i++) {
    int neighbor = graph->adj_list[vertex][i];
    if (!visited[neighbor]) {
      dfs_recursive(graph, neighbor, visited);
    }
  }
}

// function to perform depth first search
void dfs(Graph *graph, int start_vertex) {
  bool visited[MAX_VERTICES] = {false}; // track visited vertices
  printf("\ndfs traversal:\n");
  dfs_recursive(graph, start_vertex, visited);
  printf("\n");
}

// function to perform breadth first search
void bfs(Graph *graph, int start_vertex) {
  bool visited[MAX_VERTICES] = {false}; // track visited vertices
  int queue[MAX_VERTICES];              // queue for bfs
  int front = 0, rear = 0;

  visited[start_vertex] = true; // mark start_vertex as visited
  queue[rear++] = start_vertex; // enqueue the start vertex

  printf("\nbfs traversal:\n");
  while (front < rear) {
    int vertex = queue[front++]; // dequeue a vertex
    printf("%d ", vertex);

    // visit all adjacent unvisited vertices
    for (int i = 0; i < graph->list_size[vertex]; i++) {
      int neighbor = graph->adj_list[vertex][i];
      if (!visited[neighbor]) {
        queue[rear++] = neighbor; // enqueue the neighbor
        visited[neighbor] = true; // mark as visited
      }
    }
  }
  printf("\n");
}

// function to display the menu
void display_menu() {
  printf("\n---- Menu ----\n");
  printf("1. Add Edge\n");
  printf("2. Display Adjacency List\n");
  printf("3. Display Adjacency Matrix\n");
  printf("4. Perform DFS\n");
  printf("5. Perform BFS\n");
  printf("6. Display Menu\n");
  printf("7. Exit\n");
}

// function to handle user choice
void handle_choice(Graph *graph) {
  int choice, u, v, start_vertex;

  printf("\nChoice: ");
  scanf("%d", &choice);

  switch (choice) {
  case 1:
    printf("Enter edge (u v): ");
    scanf("%d %d", &u, &v);
    add_edge(graph, u, v);
    break;
  case 2:
    display_adjacency_list(graph);
    break;
  case 3:
    display_adjacency_matrix(graph);
    break;
  case 4:
    printf("Enter start vertex for DFS: ");
    scanf("%d", &start_vertex);
    dfs(graph, start_vertex);
    break;
  case 5:
    printf("Enter start vertex for BFS: ");
    scanf("%d", &start_vertex);
    bfs(graph, start_vertex);
    break;
  case 6:
    display_menu();
    break;
  case 7:
    printf("Exiting...\n");
    exit(0);
  default:
    printf("Invalid choice \n");
  }
}
