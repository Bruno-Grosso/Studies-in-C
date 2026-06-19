#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define INF 1000000

typedef struct Node{
  int vertex;
  int weight;
  struct Node* next;
}Node;

typedef struct Graph{
  int num_vertex;
  Node** vertex;
}Graph;


Graph* create_graph(int num_vertex){

  Graph* map = (Graph*)malloc(sizeof(Graph));

  map->num_vertex = num_vertex;
  map->vertex = (Node**)malloc(num_vertex*sizeof(Node*));

  for(int i=0; i<num_vertex; i++){
    map->vertex[i] = NULL;
  }

  return map;
}


Node* create_node(int destination, int weight){

  Node* my_node = (Node*)malloc(sizeof(Node));

  my_node->vertex = destination;
  my_node->weight = weight;
  my_node->next = NULL;

  return my_node;
}


void add_edge(Graph* map, int origin, int destination, int weight){

  Node* my_node = create_node(destination, weight);
  my_node->next = map->vertex[origin];
  map->vertex[origin] = my_node;

}


void data_reader(Graph* map, const char* archive_path) {
  FILE* archive = fopen(archive_path, "r");
  if (archive == NULL) {
      printf("Erro to open the archive %s\n", archive_path);
      return;
  }

  char line[4096]; 

  while (fgets(line, sizeof(line), archive) != NULL) {

      char* block = strtok(line, " \t\r\n");

      if (block != NULL) {
          int origin = atoi(block);

          block = strtok(NULL, " \t\r\n");

          while (block != NULL) {
              int destination, weight;

              if (sscanf(block, "%d,%d", &destination, &weight) == 2) {
                  add_edge(map, origin, destination, weight);
              }

              block = strtok(NULL, " \t\r\n");
          }
      }
  }

  fclose(archive);
}


void djikstra_core(Graph* map, int origin, int destination){

  int num_vertex = map->num_vertex;

  int distance[num_vertex];
  int visited[num_vertex];
  int father[num_vertex];

  for(int i=0; i<num_vertex; i++){

    distance[i] = INF;
    visited[i] = 0;
  }

  distance[origin] = 0;

  for(int count=0; count<num_vertex; count ++){

    int min_dist = INF;
    int current = -1;

    for(int i=0; i<num_vertex; i++){
      if(visited[i] == 0 && distance[i]<min_dist){
        min_dist = distance[i];
        current = i;
      }
    }

    if(current == -1){
      break;
    }

    visited[current] = 1;
    if(current == destination){
      break;
    }

    Node* temp = map->vertex[current];

    while(temp != NULL){
      int neighboor = temp->vertex;

      if(visited[neighboor] == 0){
        int next_dist = distance[current] + (temp->weight);
        
        if(next_dist < distance[neighboor]){
          distance[neighboor] = next_dist;
        }
      }

      temp = temp->next;
    }
  }
  
  printf("Distance: %d\n", distance[destination]);
  
}


int main(){
  int num_vertex = 201;

  Graph* map = create_graph(num_vertex);

  data_reader(map, "dijkstraData.txt");

  djikstra_core(map, 1, 7);
  djikstra_core(map, 1, 37);
  djikstra_core(map, 1, 59);
  djikstra_core(map, 1, 82);
  djikstra_core(map, 1, 99);
  djikstra_core(map, 1, 115);
  djikstra_core(map, 1, 133);
  djikstra_core(map, 1, 165);
  djikstra_core(map, 1, 188);
  djikstra_core(map, 1, 197);

  return 0;
}
