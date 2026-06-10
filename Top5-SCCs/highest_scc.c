#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Adjacency list node
typedef struct Node {
  int vertex;
  struct Node* next;
} Node;

// Graph structure containing an array of adjacency lists
typedef struct Graph {
  int num_vertex;
  Node** vertex; 
} Graph;

// Allocates memory for the graph and initializes adjacency lists to NULL
Graph* create_graph(int num_vertex) {
  Graph* map = (Graph*)malloc(sizeof(Graph));
  map->num_vertex = num_vertex;
  map->vertex = (Node**)malloc(num_vertex * sizeof(Node*));

  for(int i = 0; i < num_vertex; i++) {
    map->vertex[i] = NULL;
  }
  return map;
}

Node* create_node(int second) {
  Node* temp_node = (Node*)malloc(sizeof(Node));
  temp_node->vertex = second;
  temp_node->next = NULL;
  return temp_node;
}

// Adds a directed edge from 'first' to 'second' at the beginning of the list (O(1))
void add_edge(Graph* map, int first, int second) {
  Node* temp_node = create_node(second);
  temp_node->next = map->vertex[first];
  map->vertex[first] = temp_node;
}

// Pass 1: Computes finishing times on the reversed graph and pushes nodes to the stack
void first_DFS(Graph* map_rev, int i, bool* visited, int* stack, int* top) {
  visited[i] = true;
  Node* temp = map_rev->vertex[i];
  
  while(temp != NULL) {
    if(visited[temp->vertex] == 0) {
      first_DFS(map_rev, temp->vertex, visited, stack, top);
    }
    temp = temp->next;
  }

  (*top)++;
  stack[(*top)] = i;
}

// Pass 2: Explores the original graph to find an SCC and returns its size
int second_DFS(Graph* map, int v, bool* visited, int size) {
  visited[v] = true;
  size++;
  Node* temp = map->vertex[v];
  
  while(temp != NULL) {
    if(visited[temp->vertex] == 0) {
      size = second_DFS(map, temp->vertex, visited, size);
    }
    temp = temp->next;
  }
  return size;
}

// Returns the target index if the SCC size belongs in the top 5, otherwise returns -1
int compare_sizes(int size, int top_sizes[]) {
  for(int i = 0; i < 5; i++) {
    if(size > top_sizes[i]) {
      return i;
    }
  }
  return -1;
}

// Core Kosaraju's Algorithm implementation
void find_SCCs(Graph* map, Graph* map_rev) {
  int n = map->num_vertex;
  bool* visited = calloc(n, sizeof(bool));
  
  int* stack = (int*)malloc(n * sizeof(int));
  int top = -1;
 
  // Step 1: Run DFS on reversed graph to track finishing times
  for(int i = 0; i < n; i++) {
    if(visited[i] == 0) {
      first_DFS(map_rev, i, visited, stack, &top);
    }
  }

  // Reset visited array for the second pass
  for(int i = 0; i < n; i++) {
    visited[i] = 0;
  }

  int top_sizes[5] = {0}; // Automatically initializes all elements to 0

  // Step 2: Process nodes in decreasing order of finishing times
  while(top >= 0) {
    int v = stack[top];
    top--;

    if(visited[v] == 0) {
      int size = 0;
      size = second_DFS(map, v, visited, size);

      // Update the top 5 largest SCCs array
      int loc = compare_sizes(size, top_sizes);
      if(loc != -1) {
        for(int i = 4; i >= loc; i--) {
          if(loc == i) {
            top_sizes[i] = size;
          } else {
            top_sizes[i] = top_sizes[i-1];
          }
        }
      }     
    }
  }

  for(int i = 0; i < 5; i++) {
    printf("%d - ", top_sizes[i]);
  }
  
  free(visited);
  free(stack);
}

int main() {
  int num_vertex = 875715;

  Graph* map = create_graph(num_vertex);
  Graph* map_rev = create_graph(num_vertex);

  FILE* file = fopen("Graph.txt", "r");
  if(file == NULL) {
    printf("ERROR: file not found\n");
    return 1;
  }

  char line[64];
  int src, dest;

  // Fast I/O: Parsing the dataset directly from strings to avoid fscanf overhead
  while(fgets(line, sizeof(line), file)) {
    char* endptr;

    src = (int)strtol(line, &endptr, 10);
    dest = (int)strtol(endptr, NULL, 10);

    add_edge(map, src, dest);       // Original graph
    add_edge(map_rev, dest, src);   // Reversed graph
  }

  fclose(file);
  printf("Graph loaded successfully\n");

  find_SCCs(map, map_rev);
  
  return 0;
}
