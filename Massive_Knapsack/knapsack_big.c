#include <stdio.h>
#include <stdlib.h>

typedef struct Datas {
  int capacity;
  int num_itens;
  long long* array_1;
  long long* array_2;
} Datas;

Datas* create_datas() {
  Datas* datas = (Datas*)malloc(sizeof(Datas));
  scanf("%d", &datas->capacity);
  scanf("%d", &datas->num_itens);
 
  // Zero-initialization via calloc establishes DP base state
  datas->array_1 = (long long*)calloc((datas->capacity + 1), sizeof(long long));
  datas->array_2 = (long long*)calloc((datas->capacity + 1), sizeof(long long));

  return datas;
}

long long DP_core(Datas* datas, int current_item) {
  // Parity indexing toggles read/write buffers
  int decide = current_item % 2;

  long long item_weight;
  long long item_value;

  scanf("%lld", &item_value);
  scanf("%lld", &item_weight);

  for (int i = 0; i <= datas->capacity; i++) {
    if (item_weight <= i) {
      long long res_weight = i - item_weight;

      if (decide == 0) {
        long long current_value = item_value + datas->array_1[res_weight];

        if (current_value > datas->array_1[i]) {
          datas->array_2[i] = current_value;
        } else {
          datas->array_2[i] = datas->array_1[i];
        }
      } else {
        long long current_value = item_value + datas->array_2[res_weight];

        if (current_value > datas->array_2[i]) {
          datas->array_1[i] = current_value;
        } else {
          datas->array_1[i] = datas->array_2[i];
        }
     }
    } else {
      if (decide == 0) {
        datas->array_2[i] = datas->array_1[i];
      } else {
        datas->array_1[i] = datas->array_2[i];
      } 
   }  
  }

  // Call stack frame allocation scales with N
  if (current_item < datas->num_itens) {
    return DP_core(datas, current_item + 1);
  }

  if (decide == 0) {
    return datas->array_2[datas->capacity];
  } else {
    return datas->array_1[datas->capacity];
  }
}

void free_function(Datas* datas) {
  free(datas->array_1);
  free(datas->array_2);
  free(datas);
}

int main() {
  // Rebinds standard input stream to local file stream
  if (freopen("knapsack_big.txt", "r", stdin) == NULL) {
    printf("Error: archive named 'knapsack_big.txt' not found.\n");
    return 1;
  }

  Datas* datas = create_datas();

  long long value_final = DP_core(datas, 1);
  printf("Final Value = %lld\n", value_final);
  
  free_function(datas);

  return 0;
}
