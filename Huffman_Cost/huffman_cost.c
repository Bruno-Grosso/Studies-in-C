#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Struct adapted to handle high capacity constraints: 
// 'id' supports 1000+ nodes instead of a single char
// 'probability' uses long long to prevent integer overflow from high frequencies
typedef struct Node {
    bool visited;
    int id;
    long long probability;
    struct Node* lef_son;
    struct Node* dir_son;
    struct Node* parent;
} Node;

typedef struct Graph {
    int num_vertex;
    Node** vertex;
} Graph;

Graph* create_graph(int num_letters){

    Graph* graph = (Graph*)malloc(sizeof(Graph));
    // A Huffman tree for N leaves always has 2N - 1 total nodes
    int num_vertex = (2 * num_letters) - 1;

    graph->num_vertex = num_vertex;
    graph->vertex = (Node**)malloc(num_vertex * sizeof(Node*));

    for(int i = 0; i < num_vertex; i++){
        graph->vertex[i] = NULL;
    }

    return graph;
}

Node* create_node(int id, long long freq){

    Node* new_node = (Node*)malloc(sizeof(Node));

    new_node->visited = 0;
    new_node->id = id;
    new_node->probability = freq;

    // Ghost nodes initialization: hide them from the search engine until needed
    if(freq == 0){
        new_node->visited = 1;
    }

    new_node->lef_son = NULL;
    new_node->dir_son = NULL;
    new_node->parent = NULL;

    return new_node;
}

void union_function(int a, int b, Graph* graph, int unions, int num_letters){

    int pos = num_letters + unions;
    Node* union_node = graph->vertex[pos];

    // Activate the parent node and set its cumulative probability
    union_node->visited = 0;
    union_node->probability = (graph->vertex[a]->probability) + (graph->vertex[b]->probability);
    union_node->dir_son = graph->vertex[a];
    union_node->lef_son = graph->vertex[b];

    // Mark children as visited and link them to the new parent
    Node* current_node = graph->vertex[a];
    current_node->visited = 1;
    current_node->parent = union_node;

    current_node = graph->vertex[b];
    current_node->visited = 1;
    current_node->parent = union_node;
}

Graph* huffman_initial(Graph* graph, int num_letters){

    int unions = 0;
    int num_vertex = graph->num_vertex;

    // We need exactly (num_letters - 1) unions to build the full tree
    for(int i = 0; i < (num_letters - 1); i++){
        int min_letter = -1;
        int sec_min_letter = -1;

        for(int j = 0; j < num_vertex; j++){
            Node* current_node = graph->vertex[j];

            if(current_node->visited != true){

                // Initialize the two minimum pointers
                if(min_letter == -1){
                    min_letter = j;
                    continue;
                } else if(sec_min_letter == -1){
                    sec_min_letter = j;

                    // Swap if the second is smaller than the first
                    if(graph->vertex[sec_min_letter]->probability < graph->vertex[min_letter]->probability){
                        int temp = min_letter;
                        min_letter = sec_min_letter;
                        sec_min_letter = temp;
                    }
                    continue;
                }

                // Shift minimums if a smaller frequency is found
                if(current_node->probability < graph->vertex[min_letter]->probability){
                    sec_min_letter = min_letter;
                    min_letter = j;
                } else if(current_node->probability < graph->vertex[sec_min_letter]->probability){
                    sec_min_letter = j;
                }
            }
        }

        union_function(min_letter, sec_min_letter, graph, unions, num_letters);
        unions++;
    }

    return graph;
}

void huffman_function(Graph* graph, int num_letters){

    int min_cost = 99999;
    int max_cost = 0;

    // Bottom-up traversal to calculate the depth of each leaf
    for(int i = 0; i < num_letters; i++){

        int current_cost = 0;
        Node* current_node = graph->vertex[i];

        // Climb the tree until the root is reached
        while(current_node->parent != NULL){
            current_cost++;
            current_node = current_node->parent;
        }

        // Update global minimum and maximum depths independently
        if(current_cost > max_cost){
            max_cost = current_cost;
        } 
        if(current_cost < min_cost){
            min_cost = current_cost;
        }
    }

    printf("Min_cost: %d \n", min_cost);
    printf("Max_cost: %d \n", max_cost);
}

int main() {

    // Open the text file
    FILE* file = fopen("huffman.txt", "r");
    if (file == NULL) {
        printf("Error: File not found.\n");
        return 1;
    }

    int num_letters;
    // Read the first line to determine the total number of leaves
    fscanf(file, "%d", &num_letters);

    Graph* graph = create_graph(num_letters);

    // Scan the file sequentially, reading large frequencies into long long
    for(int i = 0; i < num_letters; i++){
        long long freq;
        fscanf(file, "%lld", &freq);
        graph->vertex[i] = create_node(i, freq);
    }
    fclose(file);

    // Allocate the remaining ghost nodes for the upper tree structure
    for(int i = num_letters; i < graph->num_vertex; i++){
        graph->vertex[i] = create_node(-1, 0); 
    }

    printf("File read successfully. Processing tree with %d leaves...\n", num_letters);

    graph = huffman_initial(graph, num_letters);
    huffman_function(graph, num_letters);

    // Strict memory cleanup to avoid leaks
    for(int i = 0; i < graph->num_vertex; i++){
        if(graph->vertex[i] != NULL){
            free(graph->vertex[i]); 
        }
    }
    free(graph->vertex); 
    free(graph);

    printf("Memory perfectly freed.\n");

    return 0;
}
