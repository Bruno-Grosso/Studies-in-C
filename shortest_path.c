#include<stdio.h>
#include<stdlib.h>

// Node of the adjacency list
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// Graph holding the number of vertices and the adjacency list
typedef struct Graph {
    int num_vertex;
    Node** vertex;
} Graph;

// Creates graph and fills adjacency list with NULL
Graph* create_graph(int num_vertex) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->num_vertex = num_vertex;

    graph->vertex = (Node**)malloc(num_vertex * sizeof(Node*));

    for(int i = 0; i < num_vertex; i++) {
        graph->vertex[i] = NULL;  
    }
    
    return graph;
}

// Creates a new node
Node* create_node(int destination) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->vertex = destination;
    new_node->next = NULL;
    return new_node;
}

// Adds undirected edge (Insert at Head)
void add_edge(Graph* map, int origin, int destination) {
    // Origin to destination
    Node* new_node = create_node(destination);
    new_node->next = map->vertex[origin];
    map->vertex[origin] = new_node;

    // Destination to origin
    new_node = create_node(origin);
    new_node->next = map->vertex[destination];
    map->vertex[destination] = new_node;
}

// BFS to find the shortest path
void BFS(Graph* map, int start, int target, int* visited, int* parents, int* dist) {
    int queue[100];
    int front = 0;
    int rear = 0;

    // Set up the starting node
    visited[start] = 1;
    dist[start] = 0;
    queue[rear] = start;
    rear++;

    // Keep running while there are nodes in the queue
    while (front < rear) {
        int current = queue[front];
        front++;

        // Stop if found the target
        if (current == target) {
            return;
        }

        // Check all neighbors of the current node
        Node* vizinho = map->vertex[current];

        while (vizinho != NULL) {
            int id_do_vizinho = vizinho->vertex;

            // If neighbor is unvisited, mark it and put it in the queue
            if (visited[id_do_vizinho] == 0) {
                visited[id_do_vizinho] = 1;
                dist[id_do_vizinho] = dist[current] + 1; // Count jump
                parents[id_do_vizinho] = current;        // Save parent

                queue[rear] = id_do_vizinho;
                rear++;
            }
            vizinho = vizinho->next;
        }
    }
}

int main() {
    // 1. Read graph from txt file
    FILE* file = fopen("graph_map.txt", "r");

    if(file == NULL) {
        printf("Error: Could not open the file.\n");
        return 1;
    }

    int num_vertex = 0, num_edge = 0;
    fscanf(file, "%d %d", &num_vertex, &num_edge);

    Graph* map = create_graph(num_vertex);
    int origin, destination;

    // Read edges and build the graph
    for(int i = 0; i < num_edge; i++) {
        fscanf(file, "%d %d", &origin, &destination);
        add_edge(map, origin, destination);
    }
    fclose(file);
    printf("Graph created successfully.\n");

    // 2. Setup arrays for BFS
    int* visited = calloc(num_vertex, sizeof(int));
    int* dist = (int*)malloc(num_vertex * sizeof(int));
    int* parents = (int*)malloc(num_vertex * sizeof(int));

    // Start with -1 (unreached/no parent)
    for(int i = 0; i < num_vertex; i++) {
        dist[i] = -1;
        parents[i] = -1;
    }

    // 3. Get user input
    int principal = 0;
    int target = 0;

    printf("Choose the principal vertex: ");
    scanf("%d", &principal);
    printf("Choose the target vertex: ");
    scanf("%d", &target);

    dist[principal] = 0;

    // 4. Run BFS
    BFS(map, principal, target, visited, parents, dist);

    // 5. Backtrack and print the shortest path
    if(dist[target] == -1) {
        printf("There is no path connecting router %d to router %d.\n", principal, target);
    } else {
        int path[100];
        int step_count = 0;
        int atual = target;

        // Backtrack using the parents array
        while(atual != -1) {
            path[step_count] = atual;
            step_count++;
            atual = parents[atual];
        }
        
        printf("Shortest path from %d to %d:\n", principal, target);

        // Print from start to target
        for(int i = step_count - 1; i >= 0; i--) {
            printf("%d", path[i]);

            if(i > 0) {
                printf(" -> ");
            }
        }
        printf("\nDistance: %d jumps\n", dist[target]);
    }

    // Free memory
    free(visited);
    free(dist);
    free(parents);
    
    return 0;
}
