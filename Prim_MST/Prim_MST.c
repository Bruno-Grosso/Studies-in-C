#include <stdio.h>
#include <stdlib.h>

#define MAX 999999

typedef struct Node{
    int vertex;
    int weight;
    struct Node* next;
}Node;

typedef struct Graph{
    int num_vertex;
    Node** vertex;
}Graph;

typedef struct MinHeapNode {
    int vertex;
    int weight; 
} MinHeapNode;

typedef struct MinHeap {
    int size;             
    int capacity;         
    int* pos;             
    MinHeapNode** array;  
} MinHeap;

MinHeap* create_heap(int V){
	
	MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
	
	heap->size = 0;
	heap->capacity = V;
	heap->pos = (int*)malloc(V * sizeof(int));
	heap->array = (MinHeapNode**)malloc(V * sizeof(MinHeapNode*));
	
	for(int i=0; i<V; i++){
		heap->array[i] = NULL;
	}
	
	return heap;
}

MinHeapNode* create_heap_node(int dest, int weight){
	
	MinHeapNode* new_heap_node = (MinHeapNode*)malloc(sizeof(MinHeapNode));
	
	new_heap_node->vertex = dest;
	new_heap_node->weight = weight;
	
	return new_heap_node;
}

Graph* create_graph(int V){

	Graph* graph = (Graph*)malloc(sizeof(Graph)); 

  	graph->num_vertex = V;
  	graph->vertex = (Node**)malloc(V * sizeof(Node*));
    
  	for(int i=0; i<V; i++){
    	graph->vertex[i] = NULL;
  	}

	return graph;
}

Node* create_node(int dest, int weight){
    
    Node* new_node = (Node*)malloc(sizeof(Node));
    
    new_node->vertex = dest;
    new_node->weight = weight;
    new_node->next = NULL;
    
    return new_node;
}

void add_edge(Graph* graph, int src, int dest, int weight){
    
  	Node* new_node = create_node(dest, weight);
	new_node->next = graph->vertex[src];
  	graph->vertex[src] = new_node;
    
  	new_node = create_node(src, weight);
  	new_node->next = graph->vertex[dest];
  	graph->vertex[dest] = new_node;
}


Graph* load_graph_from_file(const char* filename) {
  	FILE* file = fopen(filename, "r");
  	if (file == NULL) {
    	printf("Error: Could not open the file %s!\n", filename);
    	exit(1);
  	}

  	int V, E;
  	fscanf(file, "%d %d", &V, &E);

  	Graph* graph = create_graph(V);

  	int u, v, weight;

  	for (int i = 0; i < E; i++) {
    	fscanf(file, "%d %d %d", &u, &v, &weight);
    	add_edge(graph, u - 1, v - 1, weight);
  	}

  	fclose(file);
  	return graph;
}

void swap_nodes(MinHeap* heap, int idx_a, int idx_b){
	
	MinHeapNode* a = heap->array[idx_a];
	MinHeapNode* b = heap->array[idx_b];
	
	heap->array[idx_a] = b;
	heap->array[idx_b] = a;
	
	heap->pos[a->vertex] = idx_b;
	heap->pos[b->vertex] = idx_a;
}

void min_heapfy(MinHeap* heap, int idx){
	
	int smallest = idx;
	int left = 2 * idx + 1;
	int right = 2 * idx + 2;
	
	if(left < heap->size && heap->array[left]->weight < heap->array[smallest]->weight){
        smallest = left;        
    }
    
    if(right < heap->size && heap->array[right]->weight < heap->array[smallest]->weight){
        smallest = right;
    }
	
	if(smallest != idx){
		swap_nodes(heap, smallest, idx);
		min_heapfy(heap, smallest);
	}
	
}

MinHeapNode* extract_min(MinHeap* heap){
	
	if(heap->size == 0){
		return NULL;
	}
	
	MinHeapNode* root = heap->array[0];
	MinHeapNode* last_node = heap->array[heap->size - 1];
	
	heap->array[0] = last_node;
	
	heap->pos[root->vertex] = heap->size - 1;
	heap->pos[last_node->vertex] = 0;
	
	heap->size--;
	min_heapfy(heap, 0);
	
	return root;
}

void decrease_key(MinHeap* heap, int vertex, int weight){
	
	int i = heap->pos[vertex];     
    heap->array[i]->weight = weight; 

    while (i && heap->array[i]->weight < heap->array[(i - 1) / 2]->weight) {
        swap_nodes(heap, i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

void prim_mst(Graph* graph, int start_vertex){
    
    int size = graph->num_vertex;
    
    int in_mst[size], father[size], key[size];
    MinHeap* heap = create_heap(size);
    
    for(int i=0; i<size; i++){
    	in_mst[i] = 0;
    	father[i] = -1;
    	key[i] = MAX;
    	
    	heap->array[i] = create_heap_node(i, MAX);
    	heap->pos[i] = i;
	}
	heap->size = size;
	
	key[start_vertex] = 0;
	decrease_key(heap, start_vertex, 0);
	
	
	while(heap->size != 0){
		
		MinHeapNode* min_node = extract_min(heap);
		int u = min_node->vertex;
		in_mst[u] = 1;
		
		Node* temp = graph->vertex[u];
		
		while(temp != NULL){
			
			int neighbor = temp->vertex;
      int neighbor_weight = temp->weight;
			
			if(in_mst[neighbor] == 0 && neighbor_weight < key[neighbor]){
				
				key[neighbor] = neighbor_weight;
				father[neighbor] = u;
				decrease_key(heap, neighbor, neighbor_weight);
			}
			temp = temp->next;
		}	
	}
		
    long long total_cost = 0;
    
    for(int i=0; i<size; i++){
        if(father[i] != -1){
            total_cost += key[i];
        }
    }
    printf("Total Cost: %lld\n", total_cost);
    
}

int main(){
    
    const char* filename = "Prim_MST_edges.txt";
    
    Graph* graph = load_graph_from_file(filename);
    
    printf("Graph successfully built! (Vertex_number: %d)\n", graph->num_vertex);
    printf("Starting the Min-Heap engine...\n\n");
    
    prim_mst(graph, 0);
    
    return 0;

}
